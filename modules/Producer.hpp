#ifndef PRODUCER_H
#define PRODUCER_H

#include <random>
#include <vector>

#include <systemc.h>

#define NUM_OF_TRANSACTIONS 100000

class Producer : public sc_module {
private:
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist;
    int num_of_consumers;

public:
    std::vector<sc_fifo_out<int>> out;
    std::vector<sc_in<bool>> is_busy_in_vec;

    Producer(const sc_module_name& name, int num_of_consumers);

    void main();

    void load_balancing(int random_number);

    void round_robin(int transaction_idx, int random_number);
};

#endif
