#include <iostream>
#include <vector>
#include <queue>     // Fila de prontos
#include <algorithm> // Para ordenar os processos por tempo de chegada.
#include <iomanip>   // Para formatar a saída da tabela de métricas.


class Process {
public:
    int pid;
    int arrivalTime;
    int duration;
    int priority; 

    int conclusionTime;
    int returnTime;   // Turnaround Time
    int waitTime;

    Process(int _pid, int _arrivalTime, int _duration, int _priority)
        : pid(_pid), arrivalTime(_arrivalTime), duration(_duration), priority(_priority),
          conclusionTime(0), returnTime(0), waitTime(0) {}
};

class Scheduler {
private:
    std::vector<Process> newProcesses;       // Lista de todos os processos que serão simulados.
    std::queue<Process*> readyQueue;         // Fila de processos prontos para executar.
    std::vector<Process> concludedProcesses; // Lista para guardar os processos que já terminaram.
    int simulationTime;                      // Relógio global da simulação.
    Process* processInCPU;                   // Ponteiro para o processo que está na CPU.

public:
    Scheduler() : simulationTime(0), processInCPU(nullptr) {}

    // Adiciona um novo processo ao sistema.
    void addProcess(const Process& p) {
        newProcesses.push_back(p);
    }

    void execute() {
        // Ordenamos os processos por tempo de chegada antes de começar.
        std::sort(newProcesses.begin(), newProcesses.end(), [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

        // O loop principal da simulação avança o tempo, unidade por unidade.
        // Ele continua enquanto houver processos na lista de novos, na fila de prontos ou na CPU.
        while (!newProcesses.empty() || !readyQueue.empty() || processInCPU != nullptr) {

            // 1. VERIFICAR CHEGADA DE NOVOS PROCESSOS
            // Percorre a lista de processos que ainda não chegaram e verifica se o tempo de chegada
            // deles é igual ao tempo atual da simulação.
            while (!newProcesses.empty() && newProcesses.front().arrivalTime <= simulationTime) {
                // Se um processo chegou, ele é movido para a fila de prontos.
                // Usamos ponteiros na fila para evitar cópias desnecessárias.
                readyQueue.push(&newProcesses.front());
                std::cout << "[Tempo " << simulationTime << "] Processo " << newProcesses.front().pid << " chegou e entrou na fila de prontos." << std::endl;
                newProcesses.erase(newProcesses.begin()); // Corrigido: processosNovos -> newProcesses
            }

            // 2. LÓGICA DE DECISÃO DO ESCALONADOR (O CORAÇÃO DO FCFS)
            // Se a CPU está livre (nenhum processo executando) e a fila de prontos não está vazia...
            if (processInCPU == nullptr && !readyQueue.empty()) {
                // ...o próximo processo a executar é o que está no início da fila.
                processInCPU = readyQueue.front();
                readyQueue.pop();

                // Calcula o tempo de espera: tempo atual menos o tempo de chegada.
                processInCPU->waitTime = simulationTime - processInCPU->arrivalTime;

                std::cout << "[Tempo " << simulationTime << "] CPU ociosa. Processo " << processInCPU->pid << " selecionado para execucao." << std::endl;
            }

            // 3. SIMULAR A EXECUÇÃO NA CPU
            if (processInCPU != nullptr) {
                processInCPU->duration--;

                // Se o processo terminou...
                if (processInCPU->duration == 0) {
                    // Calcula as métricas de desempenho.
                    processInCPU->conclusionTime = simulationTime + 1;
                    processInCPU->returnTime = processInCPU->conclusionTime - processInCPU->arrivalTime;

                    std::cout << "[Tempo " << simulationTime + 1 << "] Processo " << processInCPU->pid << " terminou." << std::endl;

                    // Move o processo para a lista de concluídos e libera a CPU.
                    concludedProcesses.push_back(*processInCPU);
                    processInCPU = nullptr;
                }
            } else {
                std::cout << "[Tempo " << simulationTime << "] CPU esta ociosa, sem processos na fila." << std::endl;
            }
            
            // 4. AVANÇAR O TEMPO
            simulationTime++;
        }

        std::cout << "\nSimulacao concluida em " << simulationTime << " unidades de tempo." << std::endl;
    }

    void printMetrics() {
        std::cout << "\n--- Metricas de Desempenho Finais ---\n";
        std::cout << std::left << std::setw(10) << "PID"
                  << std::setw(15) << "Chegada"
                  << std::setw(15) << "Conclusao"
                  << std::setw(15) << "Retorno (TAT)"
                  << std::setw(10) << "Espera" << std::endl;
        
        float sumReturnTime = 0.0f;
        float sumWaitTime = 0.0f;

        // Ordena por PID para uma exibição mais limpa.
        std::sort(concludedProcesses.begin(), concludedProcesses.end(), [](const Process& a, const Process& b){
            return a.pid < b.pid;
        });

        for (const auto& p : concludedProcesses) {
            std::cout << std::left << std::setw(10) << p.pid
                      << std::setw(15) << p.arrivalTime
                      << std::setw(15) << p.conclusionTime
                      << std::setw(15) << p.returnTime
                      << std::setw(10) << p.waitTime << std::endl;
            sumReturnTime += p.returnTime;
            sumWaitTime += p.waitTime;
        }

        if (!concludedProcesses.empty()) {
            std::cout << "\nTempo Medio de Retorno: " << sumReturnTime / concludedProcesses.size() << std::endl;
            std::cout << "Tempo Medio de Espera: " << sumWaitTime / concludedProcesses.size() << std::endl;
        }
    }
};

int main() {
    // Cria uma instância do nosso escalonador.
    Scheduler scheduler;

    // Adiciona alguns processos de exemplo para a simulação.
    // Process(pid, arrivalTime, duration, priority)
    scheduler.addProcess(Process(1, 0, 8, 0));
    scheduler.addProcess(Process(2, 1, 4, 0));
    scheduler.addProcess(Process(3, 2, 9, 0));
    scheduler.addProcess(Process(4, 3, 5, 0));
    
    // Inicia a execução da simulação.
    scheduler.execute();

    // Ao final, imprime as métricas calculadas.
    scheduler.printMetrics();

    return 0;
}