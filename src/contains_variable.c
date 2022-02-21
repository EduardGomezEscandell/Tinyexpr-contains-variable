#include "contains_variable.h"

// Addapted from tinyexpr
#define TE_FUN(arg1, ...) ((arg1) || (__VA_ARGS__))
#define M(e, v, size) contains_variables((n->parameters[e]), (v), (size))

// These are copy-pasted from tiny-expr
//{

enum {TE_CONSTANT = 1};
#define TYPE_MASK(TYPE) ((TYPE)&0x0000001F)
#define ARITY(TYPE) ( ((TYPE) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((TYPE) & 0x00000007) : 0 )

//}

int item_in_variable_list(double const* item, te_variable const* array[], const size_t size)
{
    for(size_t i=0; i<size; ++i)
    {
        if(item == array[i]->address) return 1;
    }
    return 0;
}


int contains_variable(te_expr const* n, te_variable const* v)
{
     return contains_variables(n, &v, 1);
}


// Mostly based on te_eval
int contains_variables(te_expr const* n, te_variable const* v[], const size_t s)
{
    if (!n) return 0;

    switch(TYPE_MASK(n->type)) {
        case TE_VARIABLE:
        	return item_in_variable_list(n->bound, v, s);

        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(ARITY(n->type)) {
                case 0: return 0;
                case 1: return M(0, v, s);
                case 2: return TE_FUN(M(0, v, s), M(1, v, s));
                case 3: return TE_FUN(M(0, v, s), M(1, v, s), M(2, v, s));
                case 4: return TE_FUN(M(0, v, s), M(1, v, s), M(2, v, s), M(3, v, s));
                case 5: return TE_FUN(M(0, v, s), M(1, v, s), M(2, v, s), M(3, v, s), M(4, v, s));
                case 6: return TE_FUN(M(0, v, s), M(1, v, s), M(2, v, s), M(3, v, s), M(4, v, s), M(5, v, s));
                case 7: return TE_FUN(M(0, v, s), M(1, v, s), M(2, v, s), M(3, v, s), M(4, v, s), M(5, v, s), M(6, v, s));
                default: return 0;
            }

        default: return 0;
    }
}