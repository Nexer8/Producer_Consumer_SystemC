#ifndef CONSUMER_H
#define CONSUMER_H

#include <systemc.h>

class Consumer : public sc_module {
public:
    sc_fifo_in<int> in;
    sc_out<bool> is_busy_out;
    int num_of_wait_cycles;

    Consumer(const sc_module_name &name, int num_of_wait_cycles);

    void main();
};

#endif
