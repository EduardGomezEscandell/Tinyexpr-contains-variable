#include "tinyexpr.h"
#include <stdlib.h>
#include <stdio.h>


int contains_variable(te_expr const* expression, te_variable const* variable);

int contains_variables(te_expr const* expression, te_variable const* variable_array[], size_t size);