#include "contains_variable.h"

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        exit(EXIT_FAILURE);
    }

    char const* str_expr = argv[1];

    double values[NVARS] = {0,0,0,0};

    double* x = &values[0];
    double* y = &values[1];
    double* z = &values[2];
    double* t = &values[3];

    const te_variable vars[NVARS] = {
        {"x", x, 0, 0},
        {"y", y, 0, 0},
        {"z", z, 0, 0},
        {"t", t, 0, 0}
    };

    int err_code = 0;

    te_expr * expr = te_compile(str_expr, vars, NVARS, &err_code);

    int contains_x = contains_variable(expr, &vars[0]);
    int contains_y = contains_variable(expr, &vars[1]);
    int contains_z = contains_variable(expr, &vars[2]);
    int contains_t = contains_variable(expr, &vars[3]);

    printf("Contains...\nx:%d\ny:%d\nz:%d\nt:%d\n", contains_x, contains_y, contains_z, contains_t);
}