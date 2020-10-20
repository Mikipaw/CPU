//
// Created by mikipaw on 16.10.2020.
//



#define DO_PUSH{                    \
fscanf(input, "%lf", &first);       \
cpu_stack.push(first);              \
                                    \
};

#define DO_POP{                     \
cpu_stack.pop(&first);              \
};

#define DO_ADD{                     \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first + second);     \
};

#define DO_SUB{                     \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first - second);     \
};

#define DO_MUL{                     \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first * second);     \
};

#define DO_DIV{                     \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first / second);     \
};

#define DO_NEG{                     \
cpu_stack.pop(&first);              \
cpu_stack.push(-first);             \
};

#define DO_SINUS{                   \
cpu_stack.pop(&first);              \
cpu_stack.push(sin(first));         \
};

#define DO_COS{                     \
cpu_stack.pop(&first);              \
cpu_stack.push(cos(first));         \
};

#define DO_SQRT{                    \
cpu_stack.pop(&first);              \
cpu_stack.push(sqrt(first));        \
};

#define DO_POW{                     \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(pow(first, second)); \
};

#define DO_IN{                      \
printf("\nInput: \n");              \
scanf("%lf", first);                \
cpu_stack.push(first);              \
};

#define DO_OUT{                     \
cpu_stack.pop(&first);              \
printf("\nOutput: %lf\n", first);   \
};

#define DO_DUMP{                    \
Stack_info(cpu_stack);              \
};

#define DO_HLT{                     \
printf("\nProcess finishing...\n"); \
return;                             \
};

DEF_CMD( PUSH,  9,    {DO_PUSH})
DEF_CMD( POP,   10,   {DO_POP})
DEF_CMD( ADD,   0,    {DO_ADD})
DEF_CMD( SUB,   1,    {DO_SUB})
DEF_CMD( MUL,   2,    {DO_MUL})
DEF_CMD( DIV,   3,    {DO_DIV})
DEF_CMD( NEG,   4,    {DO_NEG})
DEF_CMD( SINUS, 5,    {DO_SINUS})
DEF_CMD( COS,   6,    {DO_COS})
DEF_CMD( SQRT,  7,    {DO_SQRT})
DEF_CMD( POW,   8,    {DO_POW})
DEF_CMD( IN,    11,   {DO_IN})
DEF_CMD( OUT,   12,   {DO_OUT})
DEF_CMD( DUMP,  13,   {DO_DUMP})
DEF_CMD( HLT,   14,   {DO_HLT})

/*
DEF_CMD( PUSH,  9)
DEF_CMD( POP,   10)
DEF_CMD( ADD,   0)
DEF_CMD( SUB,   1)
DEF_CMD( MUL,   2)
DEF_CMD( DIV,   3)
DEF_CMD( NEG,   4)
DEF_CMD( SINUS, 5)
DEF_CMD( COS,   6)
DEF_CMD( SQRT,  7)
DEF_CMD( POW,   8)
DEF_CMD( IN,    11)
DEF_CMD( OUT,   12)
DEF_CMD( DUMP,  13)
DEF_CMD( HLT,   14)
*/