#include "stdarch.h"
#include <stdio.h>

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

