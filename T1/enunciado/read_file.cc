#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Process.h"
#include "Scheduler.h"
#include "YourAlgorithm.h"

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}

	//getters
	int getCreationTime() { return creation_time; }
	int getDuration() { return duration; }
	int getPriority() { return priority; }

private:	
	int creation_time;
	int duration; //seconds
	int priority;
};

class File
{

public:

    File() {
        myfile.open("entrada.txt");
        if (!myfile.is_open()) {
            cout << "Erro ao abrir o arquivo!\n";
        }
    }
    
    void read_file() {
    
        int a, b, c;
        
        if (!myfile.is_open()) {
            cout << "Arquivo não está aberto!" << endl;
        }
        
        int processID = 1;  // Assuming IDs start at 1 and increment by 1
        while (myfile >> a >> b >> c) {
            Process *p = new Process(processID, a, b, c);
            processes.push_back(p);
            processID++;  // Increment the process ID for the next process
        }

        cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
    }

    void print_processes_params() {
        for (auto p : processes) {
            cout << "\nProcess ID = " << p->getProcessID() 
                 << " Arrival Time = " << p->getArrivalTime()
                 << " Burst Time = " << p->getBurstTime()
                 << " Priority = " << p->getPriority() << endl;
        }
    }

    vector<Process *> get_processes() {
        return processes;
    }

    ~File() {
        for(auto p : processes) {
            delete p;
        }
    }

private:
    ifstream myfile; 
    vector<Process *> processes;
};


int main() {
    // Read processes from the file
    File fileReader;
    fileReader.read_file();
    fileReader.print_processes_params();

    // Get processes
    vector<Process *> processes = fileReader.get_processes();

    // Start the simulations
    std::cout<< " \n\n  ======================================\n"
             << "||                                      ||\n"
             << "||  Simulação de escalonamento de CPU   ||\n"
             << "||                                      ||\n"
            << "  ======================================\n" << std::endl;

    //======================================
    // YourAlgorithm Scheduling Algorithm
    //======================================

    // Setup scheduler with FCFS algorithm
    YourAlgorithm yourAlgorithm;
    Scheduler scheduler(&yourAlgorithm);

    // Add processes to scheduler
    for(auto process : processes) {
        scheduler.addProcess(process);
    }

    // Run the scheduling simulation for FCFS
    scheduler.simulate();
    scheduler.resetProcesses(processes);
}