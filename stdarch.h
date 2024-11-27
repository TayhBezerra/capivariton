#ifndef STDARCH_GUARD
#define STDARCH_GUARD
#define MAX_OP 3
#define MAX_LINE 128

/// @enum registrators
/// @brief Enumeração que define diferentes tipos de registradores.
typedef enum registrators {
  ACC,  ///< Registrador de acumulador.
  DAT,  ///< Registrador de dados.
  EXT,  ///< Registrador externo.
  PC,   ///< Registrador do contador de programa.
  NUL, ///< Utilidade para o caso de não houver mais de um registrador.
} Registrators;

typedef enum operations {
  ADD,
  SUB,
  JMP,
  MOV,
  PRT,
  MUL,
  MOD,
  DIV,
  JEQ,
  JLT,
  JGT,
} Operations;


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

/// @brief Atribui um valor a um registrador.
/// @param val Valor a ser atribuído.
/// @param reg Ponteiro para o registrador.
void mov(int val, Registrator *reg);

/// @brief Adiciona um valor ao registrador.
/// @param val Valor a ser adicionado.
/// @param reg Ponteiro para o registrador.
void add(int val, Registrator *reg);

/// @brief Subtrai um valor ao registrador.
/// @param val Valor a ser subtraido.
/// @param reg Ponteiro para o registrador.
void sub(int val, Registrator *reg);

/// @brief Multiplica o valor do registrador por um valor.
/// @param val Valor para multiplicação.
/// @param reg Ponteiro para o registrador.
void mul(int val, Registrator *reg);

/// @brief Divide o valor do registrador por um valor.
/// @param val Valor para divisao.
/// @param reg Ponteiro para o registrador.
void div__(int val, Registrator *reg);

/// @brief Calcula o módulo do valor do registrador.
/// @param val Valor para cálculo do módulo.
/// @param reg Ponteiro para o registrador.
void mod(int val, Registrator *reg);

/// @brief Imprime um valor.
/// @param val Valor imprimir.
void prt(int val);


/// @brief Move o valor de um registrador para outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmov(Registrator *reg1, Registrator *reg2);

/// @brief Adiciona o valor de um registrador a outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void radd(Registrator *reg1, Registrator *reg2);

/// @brief Subtrai o valor de um registrador a outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rsub(Registrator *reg1, Registrator *reg2);

/// @brief Multiplica o valor de um registrador com outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmul(Registrator *reg1, Registrator *reg2);


/// @brief Divide o valor de um registrador com outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rdiv(Registrator *reg1, Registrator *reg2);

/// @brief Calcula o módulo do valor de um registrador com outro.
/// @param reg1 Ponteiro para o registrador de origem.
/// @param reg2 Ponteiro para o registrador de destino.
void rmod(Registrator *reg1, Registrator *reg2);

/// @brief Imprime o valor armazenado em um registrador.
/// @param reg Ponteiro para o registrador.
void rprint(Registrator *reg);

void jmp(int i, Registrator *pc);

void jeq(int i, Registrator *pc, Registrator *acc);

void jlt(int i, Registrator *pc, Registrator *acc);

void jgt(int i, Registrator *pc, Registrator *acc);

#endif
