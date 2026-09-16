#ifndef PROCESS_H
#define PROCESS_H

#include "CPU.h"

// Process Header File
class Process {
private:
    int processID; // Identificador do processo
    int arrivalTime; // Tempo de chegada do processo
    int burstTime; // Tempo de execução do processo
    int priority; // Prioridade do processo
    int waitingTime; // Tempo de espera do processo
    int turnaroundTime; // Tempo de retorno do processo
    int startTime; // Tempo de início do processo
    int endTime; // Tempo de término do processo
    int remainingTime; // Tempo restante de execução do processo
    int state; // Estado do processo
    CPU::Context cpuContext;  // O contexto da CPU é armazenado dentro do processo, respondendo à pergunta do trabalho

public:
    // Enumeração para os estados do processo
    enum State {
        NEW,             // Novo 
        READY,           // Pronto
        EXECUTING,       // Executando
        FINISHED         // Finalizado
    };

    // Construtor
    Process(int processID, int arrivalTime, int burstTime, int priority);

    // Destrutor
    ~Process();

    // Getters e Setters
    int getProcessID() const { return processID; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getPriority() const { return priority; }
    int getWaitingTime() const { return waitingTime; }
    int getTurnaroundTime() const { return turnaroundTime; }
    int getStartTime() const { return startTime; }
    int getEndTime() const { return endTime; }
    int getRemainingTime() const { return remainingTime; }
    int getState() const { return state; }
    
    void setWaitingTime(int wt) { waitingTime = wt; }
    void setTurnaroundTime(int tt) { turnaroundTime = tt; }
    void setBurstTime(int bt) { burstTime = bt; }
    void setPriority(int p) { priority = p; }
    void setArrivalTime(int at) { arrivalTime = at; }
    void setProcessID(int pid) { processID = pid; }
    void setStartTime(int st) { startTime = st; }
    void setEndTime(int et) { endTime = et; }
    void setRemainingTime(int rt) { remainingTime = rt; }
    void setState(int s) { state = s; }

    // Funções para salvar e obter o contexto da CPU
    void saveContext(const CPU::Context& currentContext);
    CPU::Context getContext() const;

};

#endif /* PROCESS_H */
