#ifndef CPU_H
#define CPU_H

#include <cstdint>

// Classe que representa a Unidade Central de Processamento (CPU) do simulador INE5412.
// Esta classe abstrai o funcionamento de uma CPU hipotética mencionada no trabalho.
class CPU {
public:
    // Classe aninhada que representa o contexto da CPU.
    // O contexto é usado para salvar e restaurar o estado da CPU durante as trocas de contexto entre processos.
    class Context {
    public:
        uint64_t registers[6]; // 6 registros de propósito geral, conforme especificado no trabalho.
        uint64_t SP;           // Ponteiro de pilha (Stack Pointer).
        uint64_t PC;           // Contador de programa (Program Counter).
        uint64_t ST;           // Status da CPU.

        Context();                      // Construtor padrão que inicializa os registros.
        Context(const Context& other);  // Construtor de cópia.
        ~Context();                     // Destrutor.
    };

    CPU();  // Construtor da CPU. Inicializa os registros e outros componentes.
    ~CPU(); // Destrutor da CPU.

    // Restaura o contexto atual da CPU com os valores fornecidos.
    // Isso é usado durante a troca de contexto entre processos.
    void setCurrentContext(const Context& context);
    
    // Obtém o contexto atual da CPU.
    // Isso é usado para salvar o estado atual da CPU antes de uma troca de contexto.
    Context getCurrentContext() const;

private:
    uint64_t registers[6]; // 6 registros reais de propósito geral da CPU.
    uint64_t SP;           // Ponteiro de pilha real da CPU.
    uint64_t PC;           // Contador de programa real da CPU.
    uint64_t ST;           // Status real da CPU.
};

#endif // CPU_H
