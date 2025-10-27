#include <string>
#include <vector>
#include <iostream>

// Structure to represent a process control block
struct PCB {
    std::string id;
    int priority;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int last_run_time;
    int remaining_quantum;
};

int main() {
    std::string line;
    char dummy;
    int time_quantum;
    std::vector<PCB> processes;

    // Read time quantum from standard input
    std::cin >> dummy >> time_quantum;

    // Read processes from standard input
    while (std::cin >> line) {
        PCB p;
        p.id = line;
        std::cin >> p.priority >> p.burst_time >> p.arrival_time;
        p.remaining_time = p.burst_time;
        p.last_run_time = -1;
        p.remaining_quantum = time_quantum;
        processes.push_back(p);
    }

    // TODO: Create CPU scheduler simulator
    // You can create any data structures, classes, functions helpers as you wish
    // Do not forget to include comments describing how your simulator works.
    return 0;
}
