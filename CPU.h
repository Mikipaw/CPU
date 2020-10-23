//
// Created by mikipaw on 18.10.2020.
//

#ifndef PROC_CPU_H
#define PROC_CPU_H

#include "Stack.h"
#include "enum.h"

class CPU;

enum Registers{
    RAX,        //0
    RBX,        //1
    RCX,        //2
    RDX,        //3
};

#define CREATE_CPU(name, number_of_commands, id) CPU name(number_of_commands, id, #name);

void CPU_info(const CPU& cpu);

/*! \class CPU
 *  \brief This CPU executes commands from file with codes of coammnds.
 *
 *  \param cpu_stack - stack with double numbers.
 *  \param number_of_commands - number of commands in input file with commands.
 *  \param id - id.
 *  \param version - version.
 *  \param name - name of the CPU.
 *
 *  Some details about the CPU class.
 */
class CPU{
private:
    Stack<double> cpu_stack = Stack<double>(1);
    size_t number_of_commands = 0;
    const char* name = "Unnamed CPU";
    double* reg = nullptr;

    int id = 0;
    const int version = 2;

public:
    explicit
    CPU(size_t num_of_coms, int my_id, const char* new_name):
    number_of_commands      (num_of_coms),
    id                      (my_id),
    reg                     (new double[4]),
    cpu_stack               (1, "CPU Stack"),
    name                    (new_name){
        for(int i = 0; i < 4; ++i) {
            reg[i] = 0;
        }
    };


    /*!
    *  @method void Work().
    *  @brief  Executes commands from given file.
    *
    *  @return a bool - true if operation was successful, false - if not
    */
    void
    Work();

    [[nodiscard]] const char* Get_name()    const { return name; };
    [[nodiscard]] int Get_version()         const { return version; };
    [[nodiscard]] int Get_id()              const { return id; };

    [[nodiscard]] double Get_reg (int number) const { return reg[number]; };

    ~CPU(){
        delete [] reg;
    }

};


void CPU::Work(){
    FILE* input = fopen("Output_file.txt", "rb");
    assert(input != nullptr);
    //fseek(input, 0, SEEK_SET);
    int num_of_command = 0;


    double first    = 0;
    double second   = 0;
    int    integ    = 0;
    for(int i = 0; i < number_of_commands; ++i) {
        fscanf(input, "%d", &num_of_command);
        switch (num_of_command) {
        #define DEF_CMD(name, num, code){                       \
                    case num:                                   \
                    code                                        \
                    break;                                      \
                }
        #include "commands.h"

        #undef DEF_CMD
            default:
                return;
        }

    }

    fclose(input);
}


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
}


#endif //PROC_CPU_H
