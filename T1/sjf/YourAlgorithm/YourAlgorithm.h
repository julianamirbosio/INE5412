#ifndef YOUR_ALGORITHM_H
#define YOUR_ALGORITHM_H

#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <string>

/**
 * @class YourAlgorithm
 * @brief Template para a implementação de um novo algoritmo de escalonamento.
 * * Esta classe deve herdar de 'SchedulingAlgorithm' e implementar os seus métodos virtuais puros.
 */
class YourAlgorithm : public SchedulingAlgorithm {
public:
    // Construtor
    YourAlgorithm();

    /**
     * @brief A função principal que executa a simulação do seu algoritmo.
     * É aqui que o loop de tempo e a lógica de execução dos processos devem ser implementados.
     */
    void simulate() override;

    /**
     * @brief A função de decisão do seu escalonador.
     * @param readyProcesses Um vetor contendo todos os processos que estão no estado PRONTO.
     * @return Deve retornar o ponteiro para o processo que foi selecionado para executar a seguir.
     */
    Process* sortReadyProcesses(std::vector<Process*>& readyProcesses) override;

private:
    // Altere o nome do algoritmo para que ele apareça corretamente nos resultados da simulação.
    std::string algorithmName = "Template Algorithm"; 
};

#endif // YOUR_ALGORITHM_H