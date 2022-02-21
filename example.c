#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contains_variable.h"


enum vars {X, Y, Z, T, NVARS};

void Help()
{
    printf("Usage: example.out (--help|expression)\n");
    printf("  --help: Prints this message\n");
    printf("  expression: Finds if the expression depends on x,y,z or t\n");
}


int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        Help();
        exit(EXIT_FAILURE);
    }

    if(strncmp(argv[1], "--help", 7) == 0)
    {
        Help();
        exit(EXIT_SUCCESS);
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

    printf("Expression: %s\n", str_expr);
    if(err_code)
    {
        fprintf(stderr, "           ");
        for(int i=0; i<err_code-1; ++i) fprintf(stderr, " ");
        fprintf(stderr, "^ error is near here\n");
        fprintf(stderr, "Failed to compile expression!\n");
        exit(EXIT_FAILURE);
    }

    te_variable const* spatial_variables[3] = {&vars[X], &vars[Y], &vars[Z]};

    int contains_space = contains_variables(expr, spatial_variables, 3);
    int contains_time = contains_variable(expr, &vars[T]);

    printf("Contains...\n - Space: %d\n - Time: %d\n", contains_space, contains_time);

    te_free(expr);
}