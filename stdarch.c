#include "stdarch.h"
#include <stdio.h> 

void mov(int val, Registrator *reg) {
  *(reg->addr) = val;
}

void add(int val, Registrator *reg) {
  *(reg->addr) += val;
}

void mul(int val, Registrator *reg) {
  *(reg->addr) *= val;
}

void mod(int val, Registrator *reg) {
  *(reg->addr) %= val;
}

void rmov(Registrator *reg1, Registrator *reg2) {
  mov(*(reg1->addr), reg2);
}

void radd(Registrator *reg1, Registrator *reg2) {
  add(*(reg1->addr), reg2);
}


void rmul(Registrator *reg1, Registrator *reg2) {
  mul(*(reg1->addr), reg2);
}

void rmod(Registrator *reg1, Registrator *reg2) {
  mod(*(reg1->addr), reg2);
}

void rprint(Registrator *reg) {
  printf("%d\n", *(reg->addr));
}

