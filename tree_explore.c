#include "tinyexpr/tinyexpr.h"
#include <stdlib.h>
#include <stdio.h>

enum {NVARS=4};

int contains_variable(const te_expr *n, const te_variable *v);

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

	const te_variable vars[NVARS] = {{"x", x}, {"y", y}, {"z", z}, {"t", t}};

	int err_code = 0;

	te_expr * expr = te_compile(str_expr, vars, NVARS, &err_code);

	int contains_x = contains_variable(expr, &vars[0]);
	int contains_y = contains_variable(expr, &vars[1]);
	int contains_z = contains_variable(expr, &vars[2]);
	int contains_t = contains_variable(expr, &vars[3]);

	printf("Contains...\nx:%d\ny:%d\nz:%d\nt:%d\n", contains_x, contains_y, contains_z, contains_t);
}


// Addapted from tinyexpr
#define TE_FUN(arg1, ...) ((arg1) || (__VA_ARGS__))
#define M(e, v) contains_variable((n->parameters[e]), (v))

// These are copy-pasted from tiny-expr
//{

enum {TE_CONSTANT = 1};
#define TYPE_MASK(TYPE) ((TYPE)&0x0000001F)
#define ARITY(TYPE) ( ((TYPE) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((TYPE) & 0x00000007) : 0 )

//}

// Mostly based on te_eval
int contains_variable(const te_expr *n, const te_variable *v)
{
    if (!n) return 0;

    switch(TYPE_MASK(n->type)) {
        case TE_VARIABLE:
        	return n->bound == v->address;

        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(ARITY(n->type)) {
                case 0: return 0;
                case 1: return M(0, v);
                case 2: return TE_FUN(M(0, v), M(1, v));
                case 3: return TE_FUN(M(0, v), M(1, v), M(2, v));
                case 4: return TE_FUN(M(0, v), M(1, v), M(2, v), M(3, v));
                case 5: return TE_FUN(M(0, v), M(1, v), M(2, v), M(3, v), M(4, v));
                case 6: return TE_FUN(M(0, v), M(1, v), M(2, v), M(3, v), M(4, v), M(5, v));
                case 7: return TE_FUN(M(0, v), M(1, v), M(2, v), M(3, v), M(4, v), M(5, v), M(6, v));
                default: return 0;
            }

        default: return 0;
    }
}