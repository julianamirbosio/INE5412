#include "Scheduler.h"

// Construtor da classe Scheduler que inicializa o algoritmo de escalonamento
Scheduler::Scheduler(SchedulingAlgorithm* alg) : algorithm(alg) {
    algorithm->setScheduler(this);  // Associa este escalonador ao algoritmo
    contextSwitches = 0;  // Inicializa o contador de trocas de contexto
}

// Adiciona um processo ao algoritmo de escalonamento
void Scheduler::addProcess(Process* process) {
    algorithm->addProcess(process);
}

// Obtém o próximo processo do algoritmo de escalonamento
Process* Scheduler::getNextProcess() {
    return algorithm->getNextProcess();
}

// Simula o algoritmo de escalonamento
void Scheduler::simulate() {
    algorithm->simulate();
}

// Define o algoritmo de escalonamento e reinicia o contador de trocas de contexto
void Scheduler::setAlgorithm(SchedulingAlgorithm* alg) {
    algorithm = alg;
    algorithm->setScheduler(this);
    contextSwitches = 0;
}

// Reinicia as propriedades dos processos
void Scheduler::resetProcesses(const std::vector<Process*>& processes) {
    for (Process* p : processes) {
        p->setState(Process::NEW);
        p->setWaitingTime(0);
        p->setTurnaroundTime(0);
        p->setStartTime(0);
        p->setEndTime(0);
        p->setRemainingTime(p->getBurstTime());
        // Reset other properties if necessary
    }
}

// Realiza uma troca de contexto entre dois processos
void Scheduler::contextSwitch(Process* fromProcess, Process* toProcess) {
    if (fromProcess) {
        // Salva o contexto atual da CPU no processo de origem
        fromProcess->saveContext(cpu.getCurrentContext());
    }

    if (toProcess) {
        // Restaura o contexto salvo do processo de destino para a CPU
        cpu.setCurrentContext(toProcess->getContext());
    }
    contextSwitches++;  // Incrementa o contador de trocas de contexto
}

// Destrutor da classe Scheduler
Scheduler::~Scheduler() {
    // Limpeza, se necessário
}
