#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>

#include <systemc.h>

#include "modules/TopModule.hpp"

using namespace std;

int sc_main(int argc, char *argv[]) {
    int num_of_consumers = 1;
    int num_of_wait_cycles = 30;
    int opt;
#ifdef LOAD_BALANCING
    string writing_policy = "Load Balancing";
#else
    string writing_policy = "Round Robin";
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
        }
    }

    TopModule top("Top", num_of_consumers, num_of_wait_cycles);

    sc_set_time_resolution(1, SC_PS);
    sc_start();

    cout << endl
         << "SUMMARY" << endl;
    cout << "Writing policy: " << writing_policy << endl;
    cout << "Number of consumers: " << num_of_consumers << endl;
    cout << "Number of cycles per wait: " << num_of_wait_cycles << endl;
    cout << "Duration: " << sc_time_stamp().to_double() << "ps" << endl;

    return 0;
}