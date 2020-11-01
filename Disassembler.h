//
// Created by mikipaw on 22.10.2020.
//

#ifndef PROC_DISASSEMBLER_H
#define PROC_DISASSEMBLER_H


#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"

int Disassembler();

/*
int Disassembler(){
    FILE* command_file = fopen("Output_file.txt", "rb");
    if (command_file == nullptr) {
        fprintf(stderr, "Error opening file!\n");
        return ERROR_OPENING_FILE;
    }

    size_t size_of_file         = Size_of_file(command_file);
    size_t number_of_commands   = 0;

    char* command_text = simple_text_from_file(command_file, size_of_file, &number_of_commands);
    if (command_text == nullptr)    return ERROR_NULL_PTR;
    if (number_of_commands++ == 0)  return ERROR_EMPTY_FILE;
    fclose(command_file);

    FILE* output = fopen("Translated_back_file.txt", "wb");
    if(!output) return ERROR_OPENING_FILE;

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0";
    simple_string* regss = (simple_string*) calloc(5, sizeof(simple_string));
    regss[0].string = (char*) regs;

    Arrange_str_ptrs(regss, 5, (char*) regs);

    int    rid      = 0;
    int    rip      = 0;
    double num      = 0;
    for(int i = 0; i < number_of_commands; ++i) {
        sscanf(command_text, "%d", &rip);
        command_text += (2 + rip/10);
        #define DEF_CMD(name, number, code, hash){                              \
            if(number == rip){                                                  \
                fprintf(output, "%s\n", #name);                                 \
                }                                                               \
                if(rip == CMD_PUSH) {                                           \
                    sscanf(command_text, "%d", &rid);                           \
                    (command_text) += 2;                                        \
                    if(rid == 0){                                               \
                        sscanf(command_text, "%lf", &num);                      \
                        (command_text) += 2;                                    \
                        fprintf(output, "%lf", num);                            \
                    }                                                           \
                    else fprintf(output, "%s\n", regss[rid].string);            \
                }                                                               \
                if(rip == CMD_POP) {                                            \
                sscanf(command_text, "%d", &rid);                               \
                (command_text) += 2;                                            \
                    if(rid == 0){                                               \
                        continue;                                               \
                    }                                                           \
                    else fprintf(output, "%s\n", regss[rid].string);            \
                }                                                               \
                else if(rip >= CMD_JMP && rip <= CMD_JNE) {                     \
                sscanf(command_text, "%d", &rid);                               \
                (command_text) += 2;                                            \
                fprintf(output, "%d\n", rid);                                   \
                                                                                \
                }                                                               \
        }                                                                       \

        #include "commands.h"

        #undef DEF_CMD


    }

        fclose(output);
        free(regss);
        return ALL_OK;
}
*/


int Disassembler(){
    size_t number_of_commands = 0;
    simple_string* array_with_commands = Make_array_from_simple_text_file("Output_file.txt", &number_of_commands);

    FILE* Transed_back = fopen("Translated_back.txt", "wb");

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0";
    simple_string* rip = (simple_string*) calloc(5, sizeof(simple_string));
    rip[0].string = (char*) regs;

    Arrange_str_ptrs(rip, 5, (char*) regs);

    int     mark    = 1;
    int     command = 0;
    double  num     = 0;


    int marks[5];
    int j = 1;
    for(int i = 0; i < number_of_commands; ++i){
        sscanf(array_with_commands[i].string, "%d", &command);
        if(command >= CMD_JMP && command <= CMD_JNE){
            sscanf(array_with_commands[++i].string, "%d", &command);
            marks[j++] = command;
        }
    }

    j = 1;
    for(int i = 0; i < number_of_commands; ++i){
        if(i == marks[j]){
            fprintf(Transed_back, "%d:\n", j);
            j++;
        }
        sscanf(array_with_commands[i].string, "%d", &command);
        #define DEF_CMD(name, number, code, hash){                              \
        if(command == number){                                                  \
        fprintf(Transed_back, "%s ", #name);                                    \
        if(command >= 20) {                                                     \
            sscanf(array_with_commands[++i].string, "%d", &command);            \
            if (number == CMD_PUSH && command == 0){                            \
                sscanf(array_with_commands[++i].string, "%lf", &num);           \
                fprintf(Transed_back, "%lf", num);                              \
                }                                                               \
            else if(number == CMD_PUSH || number == CMD_POP)                    \
                fprintf(Transed_back, "%s ", rip[command]);                     \
            else fprintf(Transed_back, "%d:", mark++);                          \
        }                                                                       \
        fprintf(Transed_back, "\n");                                            \
        continue;                                                               \
        }                                                                       \
        }                                                                       \

        #include "commands.h"

        #undef DEF_CMD


    }


    fclose(Transed_back);
    free(array_with_commands);
    return ALL_OK;
}
#endif //PROC_DISASSEMBLER_H
