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
    int turnaround_time;
};

void print_process_time(PCB pcb, int start_time, int end_time) {
        std::cout << "Time " << start_time << "-" << end_time << ": " << pcb.id 
        << " (Priority " << pcb.priority << ")" << std::endl;
}

//function that simulates the required scheduling process using preemptive priority and round robin
void scheduler_simulator(std::vector<PCB> processes, int time_quantum) {
    int total_CPU_time = 0;     //stores total CPU time
    int CPU_working_time = 0;   //stores time that CPU is actually working on a process
    int start_time = 0;         //stores start time for particular process
    int end_time = 0;           //stores end time for particular process
    
    PCB idle;                   //idle CPU process
    idle.id = "Idle";
    idle.priority = 0;

    std::vector<PCB> sorted_pcbs = processes;   //create sorted_pcbs vector from given processes argument

    //Sort sorted_pcbs vector using std::sort to sort processes based on arrival time
    std::sort(sorted_pcbs.begin(), sorted_pcbs.end(),
    [](const PCB& a, const PCB& b) { return a.arrival_time < b.arrival_time; });

    //Sets total time that CPU is working
    for(PCB pcb : sorted_pcbs) {
        CPU_working_time += pcb.burst_time;
    }
    total_CPU_time = CPU_working_time;

    // Iterates through each process while the CPU is still working
    int i = 0;
    while(CPU_working_time > 0) {

        while(sorted_pcbs[i].remaining_time == 0) {
            i++;
            if(i > sorted_pcbs.size()-1) i = 0;
        }


        //runs idle CPU process if process i is selected before arrival time
        if(start_time < sorted_pcbs[i].arrival_time) {
            for(int j = 0; j < (sorted_pcbs[i].arrival_time - start_time); j++) {
                end_time++;
                total_CPU_time++;
            }
            print_process_time(idle, start_time, end_time);
            start_time = end_time;
        }

        //runs selected process until completion or interruption
        for(int j = 0; j < sorted_pcbs[i].burst_time; j++) {
            sorted_pcbs[i].remaining_time--;
            CPU_working_time--;
            end_time++;

            //interrupts active process to move to higher priority process
            if(sorted_pcbs[i+1].arrival_time == end_time && sorted_pcbs[i+1].priority > sorted_pcbs[i].priority) {
                break;
            }

        }
        //prints process time information
        print_process_time(sorted_pcbs[i], start_time, end_time);
        start_time = end_time;
        i++;
        if(i > sorted_pcbs.size()-1) i = 0;
    }
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

    scheduler_simulator(processes, time_quantum);

    return 0;
}
