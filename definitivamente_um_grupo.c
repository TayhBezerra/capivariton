#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OP 3
#define MAX_LINE 128

typedef struct instr {
  char op[MAX_OP + 1];

  char reg1[MAX_OP + 1];
  int val1;

  char reg2[MAX_OP + 1];
  
  struct instr *prev;
  struct instr *next;
} Instruction;

int main(int argc, char *argv[argc + 1]) {
  return EXIT_SUCCESS;
}
