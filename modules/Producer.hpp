#ifndef PRODUCER_H
#define PRODUCER_H

#include <random>
#include <vector>

#include <systemc.h>

using namespace std;

#define NUM_OF_TRANSACTIONS 100000

class Producer : public sc_module {
private:
    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<int> dist;
    int num_of_consumers;

public:
    vector<sc_fifo_out<int>> out;
    vector<sc_in<bool>> is_busy_in_vec;

    Producer(sc_module_name name, int num_of_consumers);

    void main();

    void load_balancing(int random_number);

    void round_robin(int transaction_idx, int random_number);
};

#endif
