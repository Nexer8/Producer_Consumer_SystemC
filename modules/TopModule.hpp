#ifndef TOPMODULE_H
#define TOPMODULE_H

#include <memory>
#include <vector>

#include "Consumer.hpp"
#include "Producer.hpp"

class TopModule : public sc_module {
private:
    std::vector<std::shared_ptr<sc_fifo<int>>> fifo_inst;
    std::vector<std::shared_ptr<sc_signal<bool>>> is_busy_sig_vec;
    std::shared_ptr<Producer> producer;
    std::vector<std::shared_ptr<Consumer>> consumers;
    int num_of_consumers;
    int num_of_wait_cycles;

public:
    TopModule(const sc_module_name &name, int num_of_consumers, int num_of_wait_cycles);
};

#endif
