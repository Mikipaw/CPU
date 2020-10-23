//
// Created by mikipaw on 17.10.2020.
//

#ifndef PROC_ASSEMBLER_H
#define PROC_ASSEMBLER_H

#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"

/*!
*  \function bool Is_push(const char* str);
*  \brief Function checks if string is "PUSH "
*  \param str a const char*
*  \return true or false
*/
bool Is_push(const char* str);

/*!
*  \function int Assembler(int* number_of_cmds = nullptr);
*  \brief Classic assembler.
*  \param number_of_cmds an int* - number of commands
*  \return an integer - error code.
*/
int Assembler(int* number_of_cmds = nullptr);

/*!
*  \function void ASM_Listing();
*  \brief Function creates listing file.
*  \param number_of_cmds an int* - number of commands.
*  \return error code.
*/
int ASM_Listing();

#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

bool Is_push(const char* str){
    if(str[0] != 'P') return false;

    return str[1] == 'U' && str[2] == 'S' && str[3] == 'H' && str[4] == ' ';

}

bool Is_pop(const char* str){
    if(str[0] != 'P') return false;

    return str[1] == 'O' && str[2] == 'P';

}

int Assembler(int* number_of_cmds) {
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
    if(!output) return ERROR_OPENING_FILE;

    simple_string* commands = (simple_string*) calloc(number_of_commands, sizeof(simple_string));
    commands[0].string = command_text;

    Arrange_str_ptrs(commands, number_of_commands, command_text);

    int rid = 0;
    char* str = nullptr;
    for(int i = 0; i < number_of_commands; ++i) {
        #define DEF_CMD(name, number, code){                                    \
            if(str_cmp_upg(#name, commands[i].string) && #name[2] != 'P'){      \
                fprintf(output, "%d\n", number);                                \
                continue;                                                       \
                }                                                               \
                else if(Is_push(commands[i].string)) {                          \
                    rid =  commands[i].string[6] - 'A' + 1;                     \
                    str = &commands[i].string[5];                               \
                    if(rid < 1 || rid > 4){                                     \
                        rid = 0;                                                \
                        fprintf(output, "9\t%d\t%s", rid, str);                 \
                    }                                                           \
                    else fprintf(output, "9\t%d\n", rid);                       \
                    continue;                                                   \
                }                                                               \
                else if(Is_pop(commands[i].string)) {                           \
                    if(commands[i].size <= 5){                                  \
                        rid = 0;                                                \
                        fprintf(output, "10\t0\n");                               \
                    }                                                           \
                    else{                                                       \
                        rid =  commands[i].string[5] - 'A' + 1;                 \
                        fprintf(output, "10\t%d\n", rid);                       \
                    }                                                           \
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

int ASM_Listing(){
    size_t pos = 1;
    FILE* ASM_Listing = fopen("ASM_Listing.txt", "wb");
    FILE* ASM_Code    = fopen("Output_file.txt", "rb");

    if(!ASM_Listing || !ASM_Code) return ERROR_OPENING_FILE;

    int cmd         = 0;
    double number   = 0;
    int rid         = 0;
    char c          = 0;

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0";
    simple_string* rip = (simple_string*) calloc(5, sizeof(simple_string));
    rip[0].string = (char*) regs;

    Arrange_str_ptrs(rip, 5, (char*) regs);

    while (!feof(ASM_Code)){
        fscanf(ASM_Code, "%d", &cmd);
        if(feof(ASM_Code)) break;
        #define DEF_CMD(name, num, code) {                                                              \
            if(cmd == CMD_PUSH){                                                                        \
                fscanf(ASM_Code, "%d", &rid);                                                           \
                if(rid == 0) {                                                                          \
                    fscanf(ASM_Code, "%lf", &number);                                                   \
                    fprintf(ASM_Listing, "%d\t%d\t%d\t%lf\t\t%s %lf\n",                                 \
                    pos++, num, rid, number, #name, number);                                            \
                    }                                                                                   \
                    else                                                                                \
                    fprintf(ASM_Listing, "%d\t%d\t%d\t\t\t\t\t%s %s\n",                                 \
                    pos, num, rid, #name, rip[rid].string);                                             \
            pos+=2;                                                                                     \
            continue;                                                                                   \
            }                                                                                           \
            else if(cmd == CMD_POP){                                                                    \
                fscanf(ASM_Code, "%d", &rid);                                                           \
                if(rid == 0) fprintf(ASM_Listing, "%d\t10\t\t\t\t\t\tPOP\n", pos++);                    \
                else {                                                                                  \
                    fprintf(ASM_Listing, "%d\t10\t%d\t\t\t\t\tPOP  %s\n",                               \
                    pos++, rid, rip[rid].string);                                                       \
                }                                                                                       \
                pos++;                                                                                  \
                continue;                                                                               \
                }                                                                                       \
            else if(cmd == num && cmd != CMD_PUSH && cmd != CMD_POP){                                   \
                fprintf(ASM_Listing, "%d\t%d\t\t\t\t\t\t%s\n", pos++, num, #name);                      \
                continue;                                                                               \
            }                                                                                           \
        }                                                                                               \

        #include "commands.h"
        #undef DEF_CMD
    }

    fclose(ASM_Listing);
    fclose(ASM_Code);
    free(rip);

    return ALL_OK;
}

#undef asserted
#undef DIE



#endif //PROC_ASSEMBLER_H
