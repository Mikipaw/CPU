//
// Created by mikipaw on 11.10.2020.
//

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
    if (!Is_push(command.string)){
        switch (command_hash) {
            case 201:

            case 234:

            case 238:
            case 227:
            case 218:
            case 402:
            case 229:
            case 330:
            case 246:
            case 320:
            case 239:
            case 151:
            case 248:
            case 310:
            case 232:

            default:
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
