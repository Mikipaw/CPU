//
// Created by mikipaw on 18.10.2020.
//

#ifndef PROC_CPU_H
#define PROC_CPU_H

#include "Stack.h"
#include "enum.h"

class CPU{
private:
    Stack<double> cpu_stack = Stack<double>(1);
    size_t number_of_commands = 0;

    int id = 0;
    const int version = 2;

public:
    explicit
    CPU(size_t num_of_coms, int my_id):
    number_of_commands      (num_of_coms),
    id                      (my_id),
    cpu_stack               (1){};

    void Work(){
        FILE* input = fopen("byte_file.txt", "rb");
        assert(input != nullptr);
        //fseek(input, 0, SEEK_SET);
        int num_of_command = 0;


        double first    = 0;
        double second   = 0;
        for(int i = 0; i < number_of_commands; ++i) {
            fscanf(input, "%d", &num_of_command);
            switch (num_of_command) {
                #define DEF_CMD(name, num, code){               \
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

};


#endif //PROC_CPU_H
