//
// Created by mikipaw on 17.10.2020.
//

#ifndef PROC_ASSEMBLER_H
#define PROC_ASSEMBLER_H

#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"

#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

bool Is_push(const char* str){
    if(str[0] != 'P') return false;

    return str[1] == 'U' && str[2] == 'S' && str[3] == 'H' && str[4] == ' ';

}

int Assembler(int* number_of_cmds = nullptr) {
    FILE* command_file = fopen("command_file.txt", "rb");
    if (command_file == nullptr) {
        fprintf(stderr, "Error opening file!\n");
        return ERROR_OPENING_FILE;
    }

    size_t size_of_file         = Size_of_file(command_file);
    size_t number_of_commands   = 0;

    char* command_text = text_from_file(command_file, size_of_file, &number_of_commands);
    if (command_text == nullptr)    return ERROR_NULL_PTR;
    if (number_of_commands++ == 0)  return ERROR_EMPTY_FILE;

    FILE* output = fopen("Output_file.txt", "wb");
    output asserted;

    simple_string* commands = (simple_string*) calloc(number_of_commands, sizeof(simple_string));
    commands[0].string = command_text;

    Arrange_str_ptrs(commands, number_of_commands, command_text);

    double a = 0;
    char* str = nullptr;
    for(int i = 0; i < number_of_commands; ++i) {
        #define DEF_CMD(name, number, code){                                    \
            if(str_cmp_upg(#name, commands[i].string)){                         \
                fprintf(output, "%d\n", number);                                \
                continue;                                                       \
                }                                                               \
                else if(Is_push(commands[i].string)) {                          \
                    str = &commands[i].string[5];                               \
                    fprintf(output, "9\t%s", str);                              \
                    continue;                                                   \
                }                                                               \
        }
        #include "commands.h"

        #undef DEF_CMD
    }


    *number_of_cmds = number_of_commands;
    fclose(command_file);
    free(command_text);
    free(commands);
    fclose(output);

    return ALL_OK;
}

#undef asserted
#undef DIE

#endif //PROC_ASSEMBLER_H
