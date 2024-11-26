#include <stdio.h>
#include "stdarch.h"
#include "alloc.h"
#include <stdlib.h>
#include <string.h>

#define MAX_OP 3
#define MAX_LINE 128

Registrator* pc = NULL;
Registrator* acc = NULL;
Registrator* ext = NULL;
Registrator* dat = NULL;

typedef struct _instr {
  Operations op;
  Registrator *reg1;
  
  int val1;
  
  Registrator *reg2;
 
  struct _instr *prev;
  struct _instr *next;
} MetaInstruction;

int isRegister(MetaInstruction i) {
  return i.reg1 != NULL;
}

Registrator *loadRegSymbol(char *op) {
  Registrator *reg = 
    strcmp(op, "pc") == 0 ? pc :
    strcmp(op, "acc") == 0 ? acc :
    strcmp(op, "dat") == 0 ? dat :
    strcmp(op, "ext") == 0 ? ext : NULL;

  return reg;
}

MetaInstruction mkinstr(char *op, char *reg1, int val1, char *reg2) {
  MetaInstruction instr;
  Operations nop = 
    strcmp(op, "add") == 0 ? ADD :
    strcmp(op, "jmp") == 0 ? JMP :
    strcmp(op, "mov") == 0 ? MOV :
    strcmp(op, "prt") == 0 ? PRT :
    strcmp(op, "mul") == 0 ? MUL : MOD;

  instr.val1 = val1;
  instr.op = nop;
  instr.reg1 = loadRegSymbol(reg1);
  instr.reg2 = loadRegSymbol(reg2);
  instr.next = NULL;
  instr.prev = NULL;

  return instr;
}

void load_instr(MetaInstruction *first) {
  MetaInstruction *ptr = first;
  while (ptr != NULL) {
    switch (ptr->op) {
      case ADD:
        if (isRegister(*ptr))
          radd(ptr->reg1, acc);
        else
          add(ptr->val1, acc);
      break;
      
      case MOV:
        if (isRegister(*ptr))
          rmov(ptr->reg1, ptr->reg2);
        else
          mov(ptr->val1, ptr->reg2);
      break;
      
      case PRT:
        rprint(ptr->reg1);
      break;
      
      default:
      break;
    }

    ptr = ptr->next;
  } 
}

void init_all_reg() {
  pc = reg_alloc(PC);
  acc = reg_alloc(ACC);
  ext = reg_alloc(EXT);
  dat = reg_alloc(DAT);

  init_reg(pc, PC);   ///< Inicializa o registrador 'pc'.
  init_reg(acc, ACC); ///< Inicializa o registrador 'acc'.
  init_reg(dat, DAT); ///< Inicializa o registrador 'dat'.
  init_reg(ext, EXT); ///< Inicializa o registrador 'ext'.
}

void free_all_reg() {
  free_reg(pc);   ///< Libera memória do registrador 'pc'.
  free_reg(acc);  ///< Libera memória do registrador 'acc'.
  free_reg(dat);  ///< Libera memória do registrador 'dat'.
  free_reg(ext);  ///< Libera memória do registrador 'ext'.
}

/// @brief Função principal do programa. Inicializa e libera registradores.
/// @param argc Contagem de argumentos.
/// @param argv Array de argumentos fornecidos pela linha de comando.
/// @return Retorna `EXIT_SUCCESS` ao concluir com sucesso.
int main(int argc, char *argv[argc + 1]) {
  init_all_reg();
  
  MetaInstruction instr = mkinstr("add", "", 10, "");
  MetaInstruction instr2 = mkinstr("prt", "acc", -1, "");
  MetaInstruction instr3 = mkinstr("prt", "pc", -1, "");

  instr.next = &instr2;
  instr2.next = &instr3;
  instr2.prev = &instr;
  instr3.prev = &instr2;

  load_instr(&instr);
  free_all_reg();
  return EXIT_SUCCESS;
}

