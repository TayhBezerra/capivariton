#include "stdarch.h"
#include <stdio.h> 

void mov(int val, Registrator *reg) {
  *(reg->addr) = val;
}

void add(int val, Registrator *reg) {
  *(reg->addr) += val;
}

void sub(int val, Registrator *reg) {
  *(reg->addr) -= val;
}

void mul(int val, Registrator *reg) {
  *(reg->addr) *= val;
}

void div__(int val, Registrator *reg) {
  *(reg->addr) /= val;
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

void rsub(Registrator *reg1, Registrator *reg2) {
  sub(*(reg1->addr), reg2);
}

void rmul(Registrator *reg1, Registrator *reg2) {
  mul(*(reg1->addr), reg2);
}

void rdiv(Registrator *reg1, Registrator *reg2) {
  div__(*(reg1->addr), reg2);
}

void rmod(Registrator *reg1, Registrator *reg2) {
  mod(*(reg1->addr), reg2);
}

void rprint(Registrator *reg) {
  printf("%d\n", *(reg->addr));
}

void jmp(int i, Registrator *pc) {
  add(i, pc);
}

void jeq(int i, Registrator *pc, Registrator *acc) {
  if (*(acc->addr) == 0)
    jmp(i, pc);
}

void jlt(int i, Registrator *pc, Registrator *acc) {
  if (*(acc->addr) < 0)
    jmp(i, pc);
}


void jgt(int i, Registrator *pc, Registrator *acc) {
  if (*(acc->addr) > 0)
    jmp(i, pc);
}

