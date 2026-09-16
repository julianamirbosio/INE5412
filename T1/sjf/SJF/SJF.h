#ifndef SJF_H
#define SJF_H

#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <string>

/**
 * @class SJF
 * @brief Implementação do escalonador Shortest Job First.
 */
class SJF : public SchedulingAlgorithm {
public:
    // Construtor
    SJF();

    /**
     * @brief A função principal que executa a simulação do seu algoritmo.
     * É aqui que o loop de tempo e a lógica de execução dos processos são implementados.
     */
    void simulate() override;

    /**
     * @brief A função de decisão do seu escalonador.
     * @param readyProcesses Um vetor contendo todos os processos que estão no estado PRONTO.
     * @return Deve retornar o ponteiro para o processo que foi selecionado para executar a seguir.
     */
    Process* sortReadyProcesses(std::vector<Process*>& readyProcesses) override;

private:
    std::string algorithmName = "SJF"; 
};

#endif // SJF_H