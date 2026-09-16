#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingAlgorithm.h"  // Inclusão necessária para a classe Scheduler
#include "CPU.h"

class Scheduler {
public:
    // Construtor - recebe um ponteiro para o algoritmo de escalonamento
    Scheduler(SchedulingAlgorithm* alg);

    // Adiciona um processo ao algoritmo de escalonamento
    void addProcess(Process* process);

    // Obtém o próximo processo do algoritmo de escalonamento
    Process* getNextProcess();

    // Simula o algoritmo de escalonamento
    void simulate();

    // Define o algoritmo de escalonamento e reinicia o contador de trocas de contexto
    void resetProcesses(const std::vector<Process*>& processes);

    // Realiza uma troca de contexto entre dois processos
    void contextSwitch(Process* fromProcess, Process* toProcess);

    // Destrucor
    ~Scheduler();

    // Getters e setters

    void setAlgorithm(SchedulingAlgorithm* alg); // Seta o próximo algoritmo de escalonamento

    CPU& getCPU() { return cpu; }

    int getContextSwitches() { return contextSwitches; } // 

private:
    SchedulingAlgorithm* algorithm;  // O algoritmo de escalonamento
    CPU cpu;                         // A CPU
    int contextSwitches;         // Contador de trocas de contexto
};

#endif // SCHEDULER_H
