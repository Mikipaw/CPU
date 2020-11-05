/*!
 * @mainpage
 *  \brief     CPU
 *  \author    Michael Pavlov
 *  \author    Mikhail Pavlov
 *  \version   C++20
 *  \date      10.2020
 *  \pre       First initialize the system.
 *  \bug       No
 *  \warning
 *  \copyright GNU Public License.
 */

#include "Assembler.h"
#include "CPU.h"
#include "Disassembler.h"

#define asserted || printf("Assertion failed on line %d\n", __LINE__)

int Interface();

int main() {
    int code = Interface();
    //PrintTextFile();
    return 0;
}


int Interface(){
    int number_of_cmds = 6;
    Assembler(&number_of_cmds);
    ASM_Listing();


    CREATE_CPU(proc, number_of_cmds, 1);
    CPU_info(proc);
    int check = proc.Work();
    if(check != 0) {
        CPU_info(proc);
        return check;
    }
    Disassembler();

    size_t t = 0;
    return ALL_OK;
}
