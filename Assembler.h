//
// Created by mikipaw on 17.10.2020.
//

#ifndef PROC_ASSEMBLER_H
#define PROC_ASSEMBLER_H

#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"
#include "Onegin.h"

/*!
*  \function bool Is_push(const char* str);
*  \brief Function checks if string is "PUSH "
*  \param str a const char*
*  \return true or false
*/
bool Is_push(const char* str);

bool Is_push_reg(const char* str);

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

/*!
 * \function bool Is_jmp(const char* str);
 * \brief function checks if string is jump.
 * \param str - const char* - command.
 * \return true if true, false if not.
 */
bool Is_jmp(const char* str);

/*!
 * @function void Fill_marks(simple_string* commands, size_t* number_of_commands, int** pointers);
 * @brief Function fills the marks in array with commands.
 * @param commands - simple_string* - array with commands.
 * @param number_of_commands - size_t* - pointer to number of commands in array.
 * @param pointers - array with pointers (marks).
 * @return nothing.
 */
void Fill_marks(simple_string* commands, const size_t* number_of_commands, int* pointers);

/*!
 * @function int Hash(const char* string)
 * @brief Functions finds hash of command.
 * @param string
 * @return sum of chars in command name.
 */
int Hash(const char* string);


#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

bool Is_reg(const char* str){
    return str[0] == 'R';
    //return str[0] == 'R' && str[2] == 'X' && str[1] >= 'A' && str[1] <= 'D';
}

bool Is_push(const char* str){
    return !strncmp(str, "PUSH", 4);
}

bool Is_pop(const char* str){
    return !strncmp(str, "POP", 3);
}

bool Is_jmp(const char* str){
    return str[0] == 'J';
}

bool Is_push_reg(const char* str){
    if(str[0] != 'P')                           return false;
    if(str[5] != 'R' && str[7] != 'X')          return false;
    if(str[6] - 'A' >= 4 || str[6] - 'A' < 0)   return false;

    return true;
}


int Hash(const char* string) {
    char c = 1;
    int result = 0;

    int i = 0;
    if (string[0] == ' ') ++i;

    for (; c != ' ' && c != '\0'; ++i) {
        c = string[i];
        if(c != ' ' && c != '\n') result += (int) c;
    }
    return result;
}

void Fill_marks(simple_string* commands, const size_t* number_of_commands, int* pointers){
    int arguments = 0;
    for(int i = 0; i < *number_of_commands; ++i){
        if(     Is_pop(     commands[i].string) || Is_jmp(commands[i].string)) arguments++;
        else if( Is_push(    commands[i].string)){
             if(!Is_push_reg(commands[i].string)) arguments++;
            arguments++;
        }
        if(commands[i].string[1] == ':'){
            pointers[commands[i].string[0] - '0'] = i + arguments;
            arguments--;
            //(*number_of_commands)--;
        }
    }
}

int Assembler(int* number_of_cmds) {
    size_t number_of_commands = 0;
    simple_string* array_with_commands = Make_array_from_text_file("command_file.TXT", &number_of_commands);

    FILE* output = fopen("Output_file.txt", "wb");
    if(!output) return ERROR_OPENING_FILE;

    int* pointers = (int*) calloc(6, sizeof(int));
    Fill_marks(array_with_commands, &number_of_commands, pointers);

    int reg_number = 0;
    int chash = 0;
    int lenstr = 0;
    for(int i = 0; i < number_of_commands; ++i){
        chash = Hash(array_with_commands[i].string);
        switch (chash) {
            #define DEF_CMD(name, number, code, hash){                          \
                case hash:                                                      \
                    lenstr = strlen(#name) + 1;                                 \
                    fprintf(output, "%d ", number);                             \
                    if(Is_jmp(array_with_commands[i].string)){                  \
                    sscanf(array_with_commands[i].string + lenstr + 1, "%d", &reg_number);\
                    fprintf(output, "%d ", pointers[reg_number]);               \
                    continue;                                                   \
                }                                                               \
                if(Is_push(array_with_commands[i].string) ||                    \
                            Is_pop(array_with_commands[i].string)){             \
                    if(array_with_commands[i].string[lenstr] == 'R')        \
            fprintf(output, "%d ", array_with_commands[i].string[lenstr + 1] - 'A' + 1);\
                    else                                                        \
            fprintf(output, "0 %s ", array_with_commands[i].string + lenstr);   \
            continue;                                                           \
            }                                                                   \
                    break;                                                      \
        }                                                                       \


        #include "commands.h"
            default:
                //printf("%d\n", chash);
                break;
        #undef DEF_CMD
    }
    }

    fclose(output);
    free(pointers);
    free(array_with_commands);
    return 2;
}

int ASM_Listing(){
    size_t number_of_commands = 0;
    simple_string* array_with_commands = Make_array_from_simple_text_file("Output_file.txt", &number_of_commands);

    FILE* ASM_Listing = fopen("ASM_Listing.txt", "wb");

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0";
    simple_string* rip = (simple_string*) calloc(5, sizeof(simple_string));
    rip[0].string = (char*) regs;

    Arrange_str_ptrs(rip, 5, (char*) regs);

    int command     = 0;
    int pos         = 1;
    int arg         = 0;
    double num      = 0;
    for(int i = 0; i < number_of_commands; ++i){
        sscanf(array_with_commands[i].string, "%d", &command);
        arg = command / 20;
        switch (command) {
            #define DEF_CMD(name, number, code, hash){                                                          \
                case number:                                                                                    \
                    if(arg == 0){                                                                               \
                        fprintf(ASM_Listing, "%X\t%d\t\t\t\t%s\n", pos++, number, #name);                       \
                        break;                                                                                  \
                    }                                                                                           \
                    else if(arg == 1){                                                                          \
                        sscanf(array_with_commands[i++].string, "%*d %d", &command);                            \
                        if(Is_push(#name) || Is_pop(#name))                                                     \
                        fprintf(ASM_Listing, "%X\t%d\t%d\t\t\t%s %s\n", pos, number, command, #name, rip[command]);\
                        else                                                                                    \
                        fprintf(ASM_Listing, "%X\t%d\t%d\t\t\t%s %d\n", pos, number, command, #name, command);  \
                        pos += 2;                                                                               \
                        break;                                                                                  \
                    }                                                                                           \
                    else if(arg == 2){                                                                          \
                        sscanf(array_with_commands[i+=2].string, "%*d %d %lf", &command, &num);                 \
                        fprintf(ASM_Listing, "%X\t%d\t0\t%.2lf\t%s %lf\n", pos, number, num, #name, num);       \
                        pos += 3;                                                                               \
                        break;                                                                                  \
                    }                                                                                           \
            }

            #include "commands.h"
            default:
                printf("%d\n", command);
                break;
            #undef DEF_CMD

        }
    }

    fclose(ASM_Listing);
    free(array_with_commands);
    return ALL_OK;
}

#undef asserted
#undef DIE



#endif //PROC_ASSEMBLER_H
