// Structure to represent a process control block
struct PCB {
    string id;
    int priority;
    int burst_time;
    int arrival_time;
    int remaining_time;
    // feel free to add more variables here
};

int main() {
    string line;
    char dummy;
    int time_quantum;
    vector<PCB> processes;

    // Read time quantum from standard input
    cin >> dummy >> time_quantum;

    // Read processes from standard input
    while (cin >> line) {
        PCB p;
        p.id = line;
        cin >> p.priority >> p.burst_time >> p.arrival_time;
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
