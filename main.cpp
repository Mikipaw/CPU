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

#include "CPU.h"



int Interface();

int main() {
    int code = 0;//Interface();
    int s = charsum("HLT");
    printf("%d\n", s);
    return code;
}


int Interface(){

    FILE* command_file = fopen("command_file.txt", "rb");
    if (command_file == nullptr) {
        fprintf(stderr, "Error opening file!\n");
        return ERROR_OPENING_FILE;
    }

    size_t size_of_file         = Size_of_file(command_file);
    size_t number_of_commands   = 0;

    char* command_text = text_from_file(command_file, size_of_file, &number_of_commands);
    if (command_text == nullptr) return ERROR_NULL_PTR;
    if (number_of_commands == 0) return ERROR_EMPTY_FILE;

    simple_string* commands = (simple_string*) calloc(number_of_commands + 1, sizeof(simple_string));
    commands[0].string = command_text;

    Arrange_str_ptrs(commands, number_of_commands, command_text);
    fclose (command_file);

    Stack<double> stak(1);

    int com_code = 0;
    for (int i = 0; i <= number_of_commands; ++i){
        com_code = Do_command(&stak, commands[i]);
        if (com_code != 0) return com_code;
    }




    return ALL_OK;
}