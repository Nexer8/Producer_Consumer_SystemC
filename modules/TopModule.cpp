#include "TopModule.hpp"

TopModule::TopModule(sc_module_name name, int num_of_consumers, int num_of_wait_cycles)
    : sc_module(name),
      num_of_consumers(num_of_consumers),
      num_of_wait_cycles(num_of_wait_cycles) {

    cout << this->name() << " is created." << endl;
    producer = make_shared<Producer>("Producer1", num_of_consumers);

    for (int i = 0; i < num_of_consumers; i++) {
        fifo_inst.emplace_back(make_shared<sc_fifo<int>>(("Fifo" + to_string(i)).c_str()));
        producer->out.at(i).bind((*fifo_inst.at(i)));

        is_busy_sig_vec.emplace_back(make_shared<sc_signal<bool>>(("Sig" + to_string(i)).c_str()));
        producer->is_busy_in_vec.at(i).bind((*is_busy_sig_vec.at(i)));

        consumers.emplace_back(make_shared<Consumer>(("Consumer" + to_string(i)).c_str(), num_of_wait_cycles));
        consumers.at(i)->in.bind((*fifo_inst.at(i)));
        consumers.at(i)->is_busy_out.bind((*is_busy_sig_vec.at(i)));
    }
}
