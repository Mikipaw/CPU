//
// Created by mikipaw on 18.10.2020.
//

#ifndef PROC_CPU_H
#define PROC_CPU_H

#include "Stack.h"
#include "enum.h"
#include "cstring"

#include "myStr.h"

class CPU;

/*!
 * @enum Registers
 * @brief Registers in CPU.
 */
enum Registers{
    RAX,        //0
    RBX,        //1
    RCX,        //2
    RDX,        //3
};

#define CREATE_CPU(name, number_of_commands, id) CPU name(number_of_commands, id, #name);


/*!
 * @function void CPU_info(const CPU& cpu);
 * @param cpu - const CPU&
 * @brief Function prints some information in CPU.
 * @return nothing.
 */
void CPU_info(const CPU& cpu);


/*! @class CPU
 *  @brief This CPU executes commands from file with codes of coammnds.
 *
 *  @param cpu_stack - stack with double numbers.
 *  @param number_of_commands - number of commands in input file with commands.
 *  @param id - id.
 *  @param version - version.
 *  @param name - name of the CPU.
 *  @param ret - pointer to return back from function.
 *
 *  Some details about the CPU class.
 */
class CPU{
private:
    Stack<double> cpu_stack = Stack<double>(1);
    size_t number_of_commands = 0;
    const char* name = "Unnamed CPU";


    double* reg     = nullptr;
    double* array   = nullptr;
    int* mark       = nullptr;

    int ret = 0;
    int id = 0;
    const int version = 2;

public:
    explicit
    CPU(size_t num_of_coms, int my_id, const char* new_name):
        number_of_commands      (num_of_coms),
        id                      (my_id),
        reg                     (new double[5]),
        cpu_stack               (1, "CPU Stack"),
        mark                    (new int[5]),
        name                    (new_name)
        {
            for(int i = 0; i < 5; ++i) {
                reg[i] = 0;
                mark[i] = 0;
            }

        FILE* input = fopen("Output_file.txt", "rb");
        assert(input != nullptr);

        size_t size_of_file = Size_of_file(input);
        size_t non = 0;

        char* text = simple_text_from_file(input, size_of_file + 1, &non);
        fclose(input);

        array = (double*) calloc(non + 1, sizeof(double));

        double doub = 0;
        int i = 0;
        int j = 0;
        size_t lenstr = strlen(text);

        double magnitude = 10;
        while(pos < lenstr) {
            magnitude = 10;
            sscanf(text + pos, "%lf", &doub);
            array[j++] = doub;
            pos+=2;
            while(doub >= magnitude){
                pos++;
                magnitude*=10;
            }
            doub*=100;
            if(      (int) doub % 10  != 0) pos+=3;
            else if( (int) doub % 100 != 0) pos+=2;
        }

        number_of_commands = non;
    };

    double Get_command (int index) const { return array[index]; };


    /*!
    *  @method int Work().
    *  @brief  Executes commands from given file.
    *
    *  @return an integer - error code.
    */
    int Work();

    CPU& operator=(const CPU& cpu) = delete;
    CPU(const CPU&)                = delete;


    void Change_ret(int pointer){ ret = pointer; }

    [[nodiscard]] const char* Get_name()    const { return name; };
    [[nodiscard]] int Get_version()         const { return version; };
    [[nodiscard]] int Get_id()              const { return id; };
    [[nodiscard]] int Get_NOC()             const { return number_of_commands; };
    [[nodiscard]] int Get_ret()             const { return ret; };

    [[nodiscard]] double Get_reg (int number) const { return reg[number]; };

    ~CPU(){
        free(reg);
        //nullptr
        free(array);
        free(mark);
    }

};

void CPU_info(const CPU& cpu){
    printf("CPU = [%p], \"%s\"\n", &cpu, cpu.Get_name());
    printf("{\n");
    printf("\tversion = %d\n",      cpu.Get_version());
    printf("\tid = %d\n",           cpu.Get_id());

    printf("\tRegisters:\n");
    printf("\t{\n");
    printf("\t\tRAX = %lf\n", cpu.Get_reg(RAX));
    printf("\t\tRBX = %lf\n", cpu.Get_reg(RBX));
    printf("\t\tRCX = %lf\n", cpu.Get_reg(RCX));
    printf("\t\tRDX = %lf\n", cpu.Get_reg(RDX));
    printf("\t}\n");

    printf("\tArray:\n");
    printf("\t{\n");
    for(int i = 0; i < cpu.Get_NOC(); ++i){
        printf("\t\t%d : %X\n", i, (int) cpu.Get_command(i));
    }
    printf("\t}\n");

    printf("}\n");
}


int CPU::Work(){
    double first    = 0;
    double second   = 0;
    int    integ    = 0;
    for(int i = 0; i < number_of_commands; ++i) {
        integ = (int) array[i];
        switch (integ) {
        #define DEF_CMD(name, num, code, hash){                         \
                    case num:                                           \
                    code;                                               \
                    break;                                              \
                }
    #include "commands.h"

    #undef DEF_CMD
            default:
                return ERROR_UNKNOWN_COMMAND;
        }
    }

    return ALL_OK;
}



#endif //PROC_CPU_H
