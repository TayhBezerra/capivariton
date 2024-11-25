#include <stdlib.h>
#include "alloc.h"

void init_reg(Registrator *reg, Registrators name) {
  reg->addr = malloc(sizeof(int)); ///< Aloca memória para armazenar um inteiro.
  *(reg->addr) = 0;               ///< Inicializa o valor com 0.
  reg->name = name;               ///< Define o nome do registrador.
}

void free_reg(Registrator *reg) {
  free(reg->addr);
}

Registrator *reg_alloc(Registrators regname) {
  Registrator *reg =  malloc(sizeof(Registrator));
  reg->addr = NULL;
  reg->name = regname;
  
  return reg;
}
