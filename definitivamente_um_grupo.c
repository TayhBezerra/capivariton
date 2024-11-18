#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OP 3
#define MAX_LINE 128

/// @enum registrators
/// @brief Enumeração que define diferentes tipos de registradores.
enum registrators {
  ACC, ///< Registrador de acumulador.
  DAT, ///< Registrador de dados.
  EXT, ///< Registrador externo.
  PC,  ///< Registrador do contador de programa.
};

/// @typedef Registrators
/// @brief Tipo definido para representar os registradores.
typedef enum registrators Registrators;

/// @struct registrator
/// @brief Estrutura que representa um registrador.
/// @var registrator::name
/// Nome do registrador.
/// @var registrator::addr
/// Ponteiro para o valor armazenado pelo registrador.
typedef struct registrator {
  Registrators name;
  int *addr;
} Registrator;

/// @struct instr
/// @brief Estrutura que representa uma instrução (não utilizada no `main`).
/// @var instr::op
/// Operação representada por uma string de caracteres.
/// @var instr::reg1
/// Nome do primeiro registrador.
/// @var instr::val1
/// Valor inteiro associado ao primeiro registrador.
/// @var instr::reg2
/// Nome do segundo registrador.
/// @var instr::prev
/// Ponteiro para a instrução anterior.
/// @var instr::next
/// Ponteiro para a próxima instrução.
typedef struct instr {
  char op[MAX_OP + 1];
  char reg1[MAX_OP + 1];
  int val1;
  char reg2[MAX_OP + 1];
  struct instr *prev;
  struct instr *next;
} Instruction;

/// @brief Inicializa um registrador.
/// @param reg Ponteiro para o registrador.
/// @param name Nome do registrador.
void init_reg(Registrator *reg, Registrators name) {
  reg->addr = malloc(sizeof(int)); ///< Aloca memória para armazenar um inteiro.
  *(reg->addr) = 0;               ///< Inicializa o valor com 0.
  reg->name = name;               ///< Define o nome do registrador.
}

/// @brief Libera a memória alocada para um registrador.
/// @param reg Ponteiro para o registrador.
void free_reg(Registrator *reg) {
  free(reg->addr);
}

/// @brief Atribui um valor a um registrador.
/// @param val Valor a ser atribuído.
/// @param reg Ponteiro para o registrador.
void mov(int val, Registrator *reg) {
  *(reg->addr) = val;
}

/// @brief Adiciona um valor ao registrador.
/// @param val Valor a ser adicionado.
/// @param reg Ponteiro para o registrador.
void add(int val, Registrator *reg) {
  *(reg->addr) += val;
}

/// @brief Multiplica o valor do registrador por um valor.
/// @param val Valor para multiplicação.
/// @param reg Ponteiro para o registrador.
void mul(int val, Registrator *reg) {
  *(reg->addr) *= val;
}

/// @brief Calcula o módulo do valor do registrador.
/// @param val Valor para cálculo do módulo.
/// @param reg Ponteiro para o registrador.
void mod(int val, Registrator *reg) {
  *(reg->addr) %= val;
}

/// @brief Move o valor de um registrador para outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmov(Registrator *reg1, Registrator *reg2) {
  mov(*(reg1->addr), reg2);
}

/// @brief Adiciona o valor de um registrador a outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void radd(Registrator *reg1, Registrator *reg2) {
  add(*(reg1->addr), reg2);
}

/// @brief Multiplica o valor de um registrador com outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmul(Registrator *reg1, Registrator *reg2) {
  mul(*(reg1->addr), reg2);
}

/// @brief Calcula o módulo do valor de um registrador com outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmod(Registrator *reg1, Registrator *reg2) {
  mod(*(reg1->addr), reg2);
}

/// @brief Imprime o valor armazenado em um registrador.
/// @param reg Ponteiro para o registrador.
void rprint(Registrator *reg) {
  printf("%d\n", *(reg->addr));
}

/// @brief Função principal do programa. Inicializa e libera registradores.
/// @param argc Contagem de argumentos.
/// @param argv Array de argumentos fornecidos pela linha de comando.
/// @return Retorna `EXIT_SUCCESS` ao concluir com sucesso.
int main(int argc, char *argv[argc + 1]) {
  Registrator pc;
  Registrator acc;
  Registrator dat;
  Registrator ext;

  init_reg(&pc, PC);   ///< Inicializa o registrador 'pc'.
  init_reg(&acc, ACC); ///< Inicializa o registrador 'acc'.
  init_reg(&dat, DAT); ///< Inicializa o registrador 'dat'.
  init_reg(&ext, EXT); ///< Inicializa o registrador 'ext'.

  free_reg(&pc);   ///< Libera memória do registrador 'pc'.
  free_reg(&acc);  ///< Libera memória do registrador 'acc'.
  free_reg(&dat);  ///< Libera memória do registrador 'dat'.
  free_reg(&ext);  ///< Libera memória do registrador 'ext'.

  return EXIT_SUCCESS;
}

