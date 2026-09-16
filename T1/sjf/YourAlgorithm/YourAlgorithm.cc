#include "YourAlgorithm.h"
#include <iostream>
#include <algorithm>

YourAlgorithm::YourAlgorithm() {}

/**
 * @brief Implementa a lógica de seleção do próximo processo.
 * A classe base chama esta função, passando a lista de processos atualmente na fila de prontos.
 * Sua tarefa é decidir qual deles deve ser executado e retorná-lo.
 */
Process* YourAlgorithm::sortReadyProcesses(std::vector<Process*>& readyProcesses) {
    // Exemplo: Retornar o primeiro processo da lista (comportamento de Fila Simples).
    // Você pode adicionar lógicas mais complexas aqui, como ordenar o vetor 'readyProcesses'
    // com base no tempo de burst, prioridade, etc., antes de retornar o primeiro elemento.
    return readyProcesses.front();
}

/**
 * @brief Contém o motor da simulação do seu algoritmo.
 */
void YourAlgorithm::simulate() {
    std::cout << "-> Início algoritmo " << algorithmName << "...\n\n";

    int currentTime = 0; // Tempo atual da simulação
    Process* prevProcess = nullptr; // Processo anterior que estava em execução
    std::vector<Process*> allProcesses = processes; // Cópia para fins de impressão

    // Imprime o cabeçalho da saída
    std::cout << "tempo ";
    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    // Função auxiliar para imprimir o estado dos processos
    auto printProcessesState = [&]() {
        std::cout << " " << currentTime << "-" << (currentTime + 1) << "  ";
        for (Process* p : allProcesses) {
            switch (p->getState()) {
                case Process::EXECUTING: std::cout << "## "; break;
                case Process::READY: std::cout << "-- "; p->setWaitingTime(p->getWaitingTime()+1); break;
                default: std::cout << "   "; break;
            }
        }
        std::cout << "\n";
    };

    // A função 'isFinished()' da classe base verifica se todos os processos chegaram ao estado 'FINISHED'.
    while (!isFinished()) {
        
        // A função 'updateReadyProcesses(currentTime)' da classe base verifica se algum processo
        // chegou no tempo atual e o move para a fila de prontos.
        updateReadyProcesses(currentTime);
        
        // A função 'getNextProcess()' da classe base chama a sua implementação de 'sortReadyProcesses'
        // e retorna o processo selecionado, já o removendo da fila de prontos.
        Process* currentProcess = getNextProcess();

        // Se 'getNextProcess()' retorna nullptr, significa que a fila de prontos está vazia.
        // Neste caso, a CPU fica ociosa, e nós apenas avançamos o tempo.
        if (!currentProcess) {
            printProcessesState();
            currentTime++;
            continue;
        }

        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        currentProcess->setState(Process::EXECUTING);
        
        // ---- Lógica de Execução ----
        // O exemplo abaixo é para um algoritmo NÃO-PREEMPTIVO.
        int burstTime = currentProcess->getBurstTime();
        for (int j = 0; j < burstTime; ++j) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
        }

        // Para um algoritmo PREEMPTIVO, a lógica seria diferente. Você executaria por um quantum
        // de tempo e, se o processo não terminasse, o devolveria para a fila de prontos usando:
        //
        // if (currentProcess->getRemainingTime() > 0) {
        //     currentProcess->setState(Process::READY);
        //     returnToReadyQueue(currentProcess); // Função da classe base para preempção.
        // }
        // --------------------------

        currentProcess->setEndTime(currentTime);
        currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        currentProcess->setState(Process::FINISHED);
        prevProcess = currentProcess;
    }

    // A função 'printResults()' da classe base calcula as médias e imprime o resumo final.
    printResults(scheduler->getContextSwitches(), algorithmName);
}