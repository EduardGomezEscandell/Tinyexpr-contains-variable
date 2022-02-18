#include "tinyexpr.h"
#include <stdlib.h>
#include <stdio.h>

enum {NVARS=4};

int contains_variable(const te_expr *n, const te_variable *v);