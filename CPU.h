//
// Created by mikipaw on 11.10.2020.
//

#ifndef PROC_CPU_H
#define PROC_CPU_H

#ifndef PROC_CPU_H
#define PROC_CPU_H

#include "Stack.h"
#include "myStr.h"

enum List_of_mistakes{
    ALL_OK,                 //0
    ERROR_OPENING_FILE,     //1
    ERROR_NULL_PTR,         //2
    ERROR_EMPTY_FILE,       //3
    ERROR_UNKNOWN_COMMAND,  //4
    EXIT_CODE,              //99
};

/*!
 * @function Do_command(simple_string command);
 * @brief This function execute a command
 * @param command - simple_string
 * @return code 0 if all ok, not zero if error
 */
int Do_command(Stack<double>* stk, simple_string command);

/*!
 * @function Is_push_or_pop(const char* str);
 * @brief This function checks if command is push
 * @param str - const char*
 * @return true if push, false if not
 */
bool Is_push(const char* str);

int Do_command(Stack<double>* stk, simple_string command){
    int command_hash = charsum(command.string);
    double first  = 0;
    double second = 0;

    if (command_hash != 320){
        switch (command_hash) {
            case 201:                               //ADD
                stk->pop    (&first);
                stk->pop    (&second);
                stk->push   (first+second);
                break;

            case 234:                               //SUB
                stk->pop    (&first);
                stk->pop    (&second);
                stk->push   (second - first);
                break;

            case 238:                               //MUL
                stk->pop    (&first);
                stk->pop    (&second);
                stk->push   (first * second);
                break;

            case 227:
                stk->pop    (&first);
                stk->pop    (&second);
                stk->push   (second / first);

            case 218:
                stk->pop(&first);
                stk->push(-first);
                break;

            case 402:
                stk->pop(&first);
                stk->push(sin(first));
                break;

            case 229:
                stk->pop(&first);
                stk->push(cos(first));
                break;

            case 330:
                stk->pop(&first);
                stk->push(sqrt(first));
                break;

            case 246:
                stk->pop(&first);
                stk->pop(&second);
                stk->push(pow(second, first));
                break;

            case 239:
                stk->pop();
                break;

            case 151:
                printf("Please, enter your number:\n");
                scanf("%lf", first);
                stk->push(first);
                break;

            case 248:
                stk->pop(&first);
                printf("Result = %lf\n", first);
                break;

            case 310:
                Stack_info(*stk);
                break;

            case 232:
                printf("CPU is shutting down...\n");
                return EXIT_CODE;

            default:
                printf("Unknown command!\n");
                return ERROR_UNKNOWN_COMMAND;
        }
    }
    else{
        char* num = &command.string[5];
        int i = 0;
        while (num[i] != ' ') ++i;
        num[i] = '\0';
        char* end = &num[i];
        double dnum = strtod(num, &end);
        stk->push(dnum);
    }

    return ALL_OK;
}



bool Is_push(const char* str){
    if(str[0] != 'P') return false;

    return str[1] == 'U' && str[2] == 'S' && str[3] == 'H' && str[4] == ' ';

}




#endif //PROC_CPU_H
