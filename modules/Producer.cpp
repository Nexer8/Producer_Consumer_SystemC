#include "Producer.hpp"
#include <random>

#define RANDOM_INT_LOWER_BOUND 1
#define RANDOM_INT_UPPER_BOUND 30

using std::uniform_int_distribution;
using std::vector;

SC_HAS_PROCESS(Producer);

Producer::Producer(const sc_module_name &name, int num_of_consumers)
    : sc_module(name), num_of_consumers(num_of_consumers) {
    dist = uniform_int_distribution<int>(RANDOM_INT_LOWER_BOUND, RANDOM_INT_UPPER_BOUND);
    out = vector<sc_fifo_out<int>>(num_of_consumers);
    is_busy_in_vec = vector<sc_in<bool>>(num_of_consumers);

    cout << this->name() << " is created." << endl;

    SC_THREAD(main);
}

void Producer::load_balancing(int random_number) {
    while (true) {
        for (int i = 0; i < num_of_consumers; i++) {
            if (!is_busy_in_vec[i].read()) {
                out[i]->write(random_number);
                return;
            }
        }
        wait(1, SC_PS);
    }
}

void Producer::round_robin(int transaction_idx, int random_number) {
    while (is_busy_in_vec[transaction_idx % num_of_consumers].read()) {
        wait(1, SC_PS);
    }
    out[transaction_idx % num_of_consumers]->write(random_number);
}

void Producer::main() {
    for (int i = 0; i < NUM_OF_TRANSACTIONS; i++) {
        int random_number = dist(gen);
#ifdef LOAD_BALANCING
        this->load_balancing(random_number);
#else
        this->round_robin(i, random_number);
#endif
    }
}