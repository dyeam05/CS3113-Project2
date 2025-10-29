#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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
    int waiting_time;
};

void print_process_time(PCB pcb, int current_time) {
    std::cout << current_time << ": " << pcb.id << " (Priority " << pcb.priority << ")" << std::endl;
}


//function that simulates the required scheduling process using preemptive priority and round robin
void scheduler_simulator(std::vector<PCB> processes, int time_quantum) {
    int total_CPU_time = 0;     //stores total CPU time
    int CPU_working_time = 0;   //stores time that CPU is actually working on a process
    int current_time = 0;         //stores current CPU time
    PCB idle;                   //idle CPU process
    idle.id = "Idle";
    idle.priority = 0;
    idle.remaining_time = 0;

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

        std::cout << "Time " << current_time << "-";

        //runs idle CPU process if process i is selected before arrival time
        if(current_time < sorted_pcbs[i].arrival_time) {
            while(current_time < sorted_pcbs[i].arrival_time) {
                current_time++;
                total_CPU_time++;
                if(current_time >= sorted_pcbs[i].arrival_time) {
                    print_process_time(idle, current_time);
                    break;
                }
            }
            continue;
        }

        //if current and next process have equal priority, current process will execute for at most time_quantum units of time, then move to next process in round robin
        if(sorted_pcbs[i].priority == sorted_pcbs[i+1].priority) {
            for(int j = 0; j < time_quantum; j++) {
                if (sorted_pcbs[i].remaining_time > 0) {
                    sorted_pcbs[i].remaining_time--;
                    CPU_working_time--;
                    current_time++;
                }
            }
            print_process_time(sorted_pcbs[i], current_time);
            if(sorted_pcbs[i].remaining_time == 0) {
                sorted_pcbs[i].turnaround_time = current_time - sorted_pcbs[i].arrival_time;
                sorted_pcbs[i].waiting_time = sorted_pcbs[i].turnaround_time - sorted_pcbs[i].burst_time;
            }  
            i++;    //move to next process for round robin
        }
        //if current and previous process have equal priority, current process will execute for at most time_quantum units of time before either switching back to previous process in round robin,
        //or moving forward to next process with higher priority
        else if(sorted_pcbs[i].priority == sorted_pcbs[i-1].priority) {
            for(int j = 0; j < time_quantum; j++) {
                if (sorted_pcbs[i+1].arrival_time == current_time && sorted_pcbs[i+1].priority > sorted_pcbs[i].priority) {
                    break;
                }
                if (sorted_pcbs[i].remaining_time > 0) {
                    sorted_pcbs[i].remaining_time--;
                    CPU_working_time--;
                    current_time++;
                }
            }
            print_process_time(sorted_pcbs[i], current_time);
            if(sorted_pcbs[i].remaining_time == 0) {
                sorted_pcbs[i].turnaround_time = current_time - sorted_pcbs[i].arrival_time;
                sorted_pcbs[i].waiting_time = sorted_pcbs[i].turnaround_time - sorted_pcbs[i].burst_time;
            }
            if (sorted_pcbs[i+1].arrival_time == current_time && sorted_pcbs[i+1].priority > sorted_pcbs[i].priority) i++;
            else i--;
        }
        //process executes as normal until finishing time burst
        else {
            while(sorted_pcbs[i].remaining_time > 0 ) {
                if (sorted_pcbs[i].remaining_time > 0) {
                    sorted_pcbs[i].remaining_time--;
                    CPU_working_time--;
                    current_time++;
                }

                if((sorted_pcbs[i+1].arrival_time == current_time && sorted_pcbs[i+1].priority > sorted_pcbs[i].priority) || sorted_pcbs[i].remaining_time == 0) {
                    print_process_time(sorted_pcbs[i], current_time);
                    //calculate turnaround and burst time if process has finished execution
                    if(sorted_pcbs[i].remaining_time == 0) {
                        sorted_pcbs[i].turnaround_time = current_time - sorted_pcbs[i].arrival_time;
                        sorted_pcbs[i].waiting_time = sorted_pcbs[i].turnaround_time - sorted_pcbs[i].burst_time;
                    }
                    if(sorted_pcbs[i+1].arrival_time == current_time && sorted_pcbs[i+1].priority > sorted_pcbs[i].priority) i++;
                    else i = 0;
                    break;
                }
            }
        }



    }

    std::cout << "Turnaround Time" << std::endl;
    for(PCB pcb : sorted_pcbs) {
        std::cout << pcb.id << " = " << pcb.turnaround_time << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Waiting Time" << std::endl;
    for(PCB pcb : sorted_pcbs) {
        std::cout << pcb.id << " = " << pcb.waiting_time << std::endl;
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
