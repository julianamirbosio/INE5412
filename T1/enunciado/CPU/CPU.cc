#include "CPU.h"
// Implementação da classe CPU para o simulador INE5412.

// Construtor padrão para a classe Context da CPU.
// Inicializa todos os registros e componentes com 0.
CPU::Context::Context() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
    SP = 0;
    PC = 0;
    ST = 0;
}

// Construtor de cópia para a classe Context.
// Copia os valores dos registros e outros componentes do contexto fornecido.
CPU::Context::Context(const Context& other) {
    for (int i = 0; i < 6; ++i) {
        registers[i] = other.registers[i];
    }
    SP = other.SP;
    PC = other.PC;
    ST = other.ST;
}

// Destrutor da classe Context.
// Como não há alocação dinâmica de recursos, o corpo do destrutor é mantido vazio.
CPU::Context::~Context() {
    // Nada a ser feito aqui.
}

// Construtor da classe CPU.
// Inicializa todos os registros e componentes da CPU com 0.
CPU::CPU() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
    SP = 0;
    PC = 0;
    ST = 0;
}

// Destrutor da classe CPU.
// Como não há alocação dinâmica de recursos, o corpo do destrutor é mantido vazio.
CPU::~CPU() {
    // Nada a ser feito aqui.
}

// Define o contexto atual da CPU com base no contexto fornecido.
void CPU::setCurrentContext(const Context& context) {
    for (int i = 0; i < 6; ++i) {
        registers[i] = context.registers[i];
    }
    SP = context.SP;
    PC = context.PC;
    ST = context.ST;
}

// Obtém e retorna o contexto atual da CPU.
CPU::Context CPU::getCurrentContext() const {
    Context context;
    for (int i = 0; i < 6; ++i) {
        context.registers[i] = registers[i];
    }
    context.SP = SP;
    context.PC = PC;
    context.ST = ST;
    return context;
}
