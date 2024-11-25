#include "stdarch.h"

/// @brief Inicializa um registrador.
/// @param reg Ponteiro para o registrador.
/// @param name Nome do registrador.
void init_reg(Registrator *reg, Registrators name);


/// @brief Libera a memória alocada para um registrador.
/// @param reg Ponteiro para o registrador.
void free_reg(Registrator *reg);

Registrator *reg_alloc(Registrators regname);
