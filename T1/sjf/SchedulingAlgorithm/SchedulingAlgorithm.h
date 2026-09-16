#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include "Process.h"

class Scheduler; // Declaração antecipada da classe Scheduler

class SchedulingAlgorithm
{
public:
    virtual ~SchedulingAlgorithm() {}
    virtual void simulate() = 0;

    void addProcess(Process* process) {
        processes.push_back(process);
        processPid[process->getProcessID()] = process;
    }

    void addProcesses(const std::vector<Process*>& processVec) {
        for (Process* process : processVec) {
            addProcess(process);
        }
    }

    void updateReadyProcesses(int currentTime) {
        for (Process* p : processes) {
            if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
                p->setState(Process::READY);
                readyQueue.push_back(p);
            }
        }
    }

    bool isFinished() const {
        for (const auto& pair : processPid) {
            if (pair.second->getState() != Process::FINISHED) {
                return false;
            }
        }
        return true;
    }

    void setScheduler(Scheduler* sched) {
        scheduler = sched;
    }

    virtual Process* getNextProcess() {
        if (readyQueue.empty()) {
            return nullptr;
        }
        Process* selectedProcess = sortReadyProcesses(readyQueue);
        auto it = std::find(readyQueue.begin(), readyQueue.end(), selectedProcess);
        if (it != readyQueue.end()) {
            readyQueue.erase(it);
        }
        return selectedProcess;
    }

    // Calcula o tempo médio de turnaround
    virtual float calculateAverageTurnaroundTime() {
        float average = 0;
        for (auto& pair : processPid) {
            average += pair.second->getTurnaroundTime();
        }
        average /= processPid.size();
        return average; // CORREÇÃO: Adicionada a linha de retorno
    }

    // Calcula o tempo médio de espera
    virtual float calculateAverageWaitingTime() {
        float average = 0;
        for (auto& pair : processPid) {
            average += pair.second->getWaitingTime();
        }
        average /= processPid.size();
        return average; // CORREÇÃO: Adicionada a linha de retorno
    }

    // Imprime os resultados da simulação
    virtual void printResults(int contextSwitchCount, std::string algorithmName) {
        std::cout << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Tempo de Turnaround para cada processo: " << "\n";
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getTurnaroundTime)() << "\n";
        }
        std::cout << "Média = " << calculateAverageTurnaroundTime() << "\n";
        std::cout << "\n";
        std::cout << "Tempo de espera para cada processo: " << "\n";
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getWaitingTime()) << "\n";
        }
        std::cout << "Média = " << calculateAverageWaitingTime() << "\n";
        std::cout << "\nTrocas de Contexto: " << contextSwitchCount << "\n";
        std::cout << "Algoritmo: " << algorithmName << " Fim.\n";
        std::cout << "========================================\n\n";
    }

protected:
    Scheduler* scheduler = nullptr;
    std::vector<Process*> processes;
    std::vector<Process*> readyQueue;
    std::map<int, Process*> processPid;

    void returnToReadyQueue(Process* p) {
        readyQueue.push_back(p);
    }

    virtual Process* sortReadyProcesses(std::vector<Process*>& readyProcesses) = 0;
};

#endif // SCHEDULINGALGORITHM_H