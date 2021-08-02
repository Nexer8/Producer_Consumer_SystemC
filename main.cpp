#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>

#include <systemc.h>

#include "modules/TopModule.hpp"

#define DEFAULT_NO_OF_CONSUMERS 1
#define DEFAULT_NO_OF_WAIT_CYCLES 30

using std::string;

int sc_main(int argc, char *argv[]) {
    int num_of_consumers = DEFAULT_NO_OF_CONSUMERS;
    int num_of_wait_cycles = DEFAULT_NO_OF_WAIT_CYCLES;
    int opt;
#ifdef LOAD_BALANCING
    const string writing_policy = "Load Balancing";
#else
    const string writing_policy = "Round Robin";
#endif

    while ((opt = getopt(argc, argv, "p:c:")) != -1) {
        switch (opt) {
            case 'p':
                num_of_wait_cycles = atoi(optarg);
                cout << "Cycles: " << num_of_wait_cycles << endl;
                break;
            case 'c':
                num_of_consumers = atoi(optarg);
                cout << "Consumers: " << num_of_consumers << endl;
                break;
            case '?':
                cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
                break;
            default:
                break;
        }
    }

    TopModule top("Top", num_of_consumers, num_of_wait_cycles);

    sc_set_time_resolution(1, SC_PS);
    sc_start();

    cout << endl
         << "SUMMARY" << endl
         << "Writing policy: " << writing_policy << endl
         << "Number of consumers: " << num_of_consumers << endl
         << "Number of cycles per wait: " << num_of_wait_cycles << endl
         << "Duration: " << sc_time_stamp().to_double() << "ps" << endl;

    return 0;
}
