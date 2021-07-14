#include "Consumer.hpp"

SC_HAS_PROCESS(Consumer);

Consumer::Consumer(const sc_module_name &name, int num_of_wait_cycles)
    : sc_module(name), num_of_wait_cycles(num_of_wait_cycles) {
    cout << this->name() << " is created." << endl;
    SC_THREAD(main);
}

void Consumer::main() {
    int num;

    while (true) {
        in->read(num);
        is_busy_out.write(true);

        wait(num_of_wait_cycles, SC_PS);

        is_busy_out.write(false);
        cout << this->name() << ": " << num << endl;
    }
}
