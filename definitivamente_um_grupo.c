#include <stdio.h>
#include "stdarch.h"
#include "alloc.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

typedef struct queue {
  MetaInstruction *head;
} Queue;

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

MetaInstruction mkinstr(Operations op, char *reg1, int val1, char *reg2) {
  MetaInstruction instr; 

  instr.val1 = val1;
  instr.op = op;
  instr.reg1 = loadRegSymbol(reg1);
  instr.reg2 = loadRegSymbol(reg2);
  instr.next = NULL;
  instr.prev = NULL;

  return instr;
}

void insert(MetaInstruction *head, MetaInstruction *i) {
  MetaInstruction *ptr = head;
  if (ptr == NULL)
    return;

  while (ptr->next != NULL)
    ptr = ptr->next;

  ptr->next = i;
  i->prev = ptr;
}

void load_op(MetaInstruction *i) {
  switch (i->op) {
      case ADD:
        if (isRegister(*i))
          radd(i->reg1, acc);
        else
          add(i->val1, acc);
      break;

      case SUB:
        if (isRegister(*i))
          rsub(i->reg1, acc);
        else
          sub(i->val1, acc);
      break;
      
      case MOV:
        if (isRegister(*i))
          rmov(i->reg1, i->reg2);
        else
          mov(i->val1, i->reg2);
      break;
      
      case MUL:
        if (isRegister(*i))
          rmul(i->reg1, acc);
        else
          mul(i->val1, acc);
      break;

      case DIV:
        if (isRegister(*i))
          rdiv(i->reg1, acc);
        else
          div__(i->val1, acc);
      break;
      
      case JMP:
        jmp(i->val1, pc);
      break;
      
      case JEQ:
        jeq(i->val1, pc, acc);
      break;

      case JLT:
        jlt(i->val1, pc, acc);
      break;

      case JGT:
        jgt(i->val1, pc, acc);
      break;

      case PRT:
        if (isRegister(*i))
          rprint(i->reg1);
        else
          prt(i->val1);
      break;
      
      case MOD:
        if (isRegister(*i))
          rmod(i->reg1, acc);
        else
          mod(i->val1, acc);
      break;

  }

  if (i->op != JMP &&
      i->op != JEQ &&
      i->op != JLT &&
      i->op != JGT)
    jmp(1, pc);
}

void load_instr(MetaInstruction *first) {
  int counter = 0;
  MetaInstruction *ptr = first;
  
  while (ptr != NULL) {
    load_op(ptr);

    if (counter > *(pc->addr)) {
      for (size_t i = counter - *(pc->addr); i > 0; i--) {
        ptr = ptr->prev;
        counter--;
      }
    } else {
      for (size_t i = *(pc->addr) - counter; i > 0; i--) {
        ptr = ptr->next;
        counter++;
      }
    }
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

void free_instr(MetaInstruction *n) {
  if (n != NULL && n->next != NULL)
    free_instr(n->next);

  free(n);
}

char *rmxspace(char string[MAX_LINE + 1]) {
   /* Variable Declaration and Initialization. */
  char *output = malloc(sizeof(char) * (MAX_LINE + 1));
  int c = 0, d = 0;

  while (string[c] != '\0') {
    if (string[c] != ' ' || string[c + 1] != ' ') {
      output[d] = string[c];
      d++;
    }
    c++;
  }

  output[d] = '\0';
  return output;
}

void rmcomment(char *str) {
  size_t len = strlen(str);
  size_t i = 0;
  while (str[i] != '#' && str[i] != '\0')
    i++;
  
  str[i++] = '\0';
  for (; i < len; i++)
    str[i] = 0;
}

void ltrim(char *str) {
    int i = 0;

    while (str[i] != '\0' && isspace((unsigned char)str[i])) {
        i++;
    }

    if (i > 0) {
        int j = 0;
        while (str[i] != '\0')
            str[j++] = str[i++];
        str[j] = '\0';
    }
}

char *normalize_string(char str[MAX_LINE + 1]) {
  char *nStr = rmxspace(str);
  rmcomment(nStr);
  ltrim(nStr);

  return nStr;
}

Operations loadOpSym(char *op) {
  Operations nop = 
    strcmp(op, "add") == 0 ? ADD :
    strcmp(op, "sub") == 0 ? SUB :
    strcmp(op, "div") == 0 ? DIV :
    strcmp(op, "jmp") == 0 ? JMP :
    strcmp(op, "jeq") == 0 ? JEQ :
    strcmp(op, "jlt") == 0 ? JLT :
    strcmp(op, "jgt") == 0 ? JGT :
    strcmp(op, "mov") == 0 ? MOV :
    strcmp(op, "prt") == 0 ? PRT :
    strcmp(op, "mul") == 0 ? MUL : MOD;
  return nop;
}

/// Importado de TayhBezerra
/// @brief Função para identificar se uma string é um número inteiro
/// @param ptr String a ser analisada
/// @return Retorna 1 se a string for um número inteiro, caso contrário , retorna 0.
int identifyIntegers(const char *ptr){
  char *endptr;
  strtol(ptr, &endptr, 10); //Tentar converter a string para inteiro.
  return *endptr == '\0'; //Verifica se todos os caracteres foram consumidos.
}

// @brief Recebe uma string normalizada e cria a instruction
MetaInstruction *intprt(char *str) {
  MetaInstruction *i = malloc(sizeof(MetaInstruction));
  Operations op;
  int val1 = -1;
  char *reg1 = malloc(sizeof(char) * 4);
  char *reg2 = malloc(sizeof(char) * 4);

  char *p = strtok(str, " ");
  op = loadOpSym(p);

  p = strtok(NULL, " ");
  if (identifyIntegers(p))
    val1 = atoi(p);
  else
    strcpy(reg1, p);

  p = strtok(NULL, " ");
  if (p != NULL)
    strcpy(reg2, p);
  
  MetaInstruction shallow = mkinstr(op, reg1, val1, reg2);
  i->op = shallow.op;
  i->reg1 = shallow.reg1;
  i->val1 = shallow.val1;
  i->reg2 = shallow.reg2;

  return i;
}

void insert_queue(Queue *q, MetaInstruction *i) {
  if (q->head == NULL)
    q->head = i;
  else
    insert(q->head, i);
}

// @brief Le um arquivo e retorna a cadeia de MetaInstruction;
Queue *read_file(const char *path) {
  FILE *f = fopen(path, "r");
  
  Queue *q = malloc(sizeof(Queue));
  q->head = NULL;
  
  char line[MAX_LINE + 1];

  while (fgets(line, MAX_LINE + 1, f) != NULL) {
    line[strcspn(line, "\n")] = 0; // remove o \n deixado do fgets
    char *nStr = normalize_string(line);
    
    if (strlen(nStr) > 0) {
      insert_queue(q, intprt(nStr));
    }
      
    free(nStr);
  }

  fclose(f);
  return q;
}

/// @brief Função principal do programa. Inicializa e libera registradores.
/// @param argc Contagem de argumentos.
/// @param argv Array de argumentos fornecidos pela linha de comando.
/// @return Retorna `EXIT_SUCCESS` ao concluir com sucesso.
int main(int argc, char *argv[argc + 1]) {
  init_all_reg();
  
  Queue *q = read_file(argv[1]);
  load_instr(q->head);

  free_instr(q->head);
  free(q);
  free_all_reg();
  return EXIT_SUCCESS;
}

