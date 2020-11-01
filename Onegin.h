//
// Created by pawlo on 28.10.2020.
//

#ifndef PROC_ONEGIN_H
#define PROC_ONEGIN_H



/*!@function Make_array_from_text_file
 * @brief Function makes array with simple_strings from txt file.
 * @param file_path - const char*, path to txt file.
 * @param number_of_cmds - size_t* - variable equal to number of elements in array.
 * @return simple_string array.
 */
simple_string* Make_array_from_text_file(const char* file_path, size_t* number_of_cmds);


size_t Size_of_File(FILE* name_of_file) {
    fseek(name_of_file, 0, SEEK_END);
    size_t size_of_file = ftell(name_of_file);
    fseek(name_of_file, 0, SEEK_SET);

    return size_of_file;
}


int Arrange_string_ptrs(simple_string* pointers, const size_t number_of_lines, char* text) {
    assert(pointers != nullptr);
    assert(text != nullptr);
    int number_of_empty_lines = 0;
    //char *ptr = text;
    for (int i = 1; i < number_of_lines; ++i) {
        text = strchr(text, ' ');
        text++;
        pointers[i].string = text;
        pointers[i - 1].size = (int) (pointers[i].string - pointers[i - 1].string);
    }

    return number_of_empty_lines;
}

char* Text_from_file(FILE* file_name, size_t size_of_file, size_t* number_of_lines){
    char* result_string = (char*) calloc(size_of_file + 5, sizeof(char));
    fread(result_string, sizeof(char), size_of_file + 5, file_name);

    for(int i = 0; i < size_of_file; ++i){
        if(result_string[i] == '\r'){
            result_string[i++]  = '\0';
            result_string[i]    = ' ';
            (*number_of_lines)++;
        }
    }
    return result_string;
}



simple_string* Make_array_from_text_file(const char* file_path, size_t* number_of_cmds){
    FILE* command_file = fopen(file_path, "rb");
    try {
        if (command_file == nullptr) {
            throw "Can't open file!";
        }
    } catch (const char* exception) {
        fprintf(stderr, "Error: %s\n", exception);
    }

    size_t size_of_file         = Size_of_file(command_file);
    size_t number_of_commands   = 0;

    char* command_text = text_from_file(command_file, size_of_file, &number_of_commands);
    try {
        if (command_text == nullptr)    throw "zero pointer";
        if (number_of_commands++ == 0)  throw "file is empty";
    } catch (const char* exception) {
        fprintf(stderr, "Error: %s\n", exception);
    }

    simple_string* str_array = (simple_string*) calloc(number_of_commands, sizeof(simple_string));
    str_array[0].string = command_text;

    Arrange_str_ptrs(str_array, number_of_commands, command_text);

    *number_of_cmds = number_of_commands;

    return str_array;
}



simple_string* Make_array_from_simple_text_file(const char* file_path, size_t* number_of_cmds){
    FILE* command_file = fopen(file_path, "rb");
    try {
        if (command_file == nullptr) {
            throw "Can't open file!";
        }
    } catch (const char* exception) {
        fprintf(stderr, "Error: %s\n", exception);
    }

    size_t size_of_file         = Size_of_file(command_file);
    size_t number_of_commands   = 0;

    char* command_text = (char*) calloc(size_of_file, sizeof(char));
    fread(command_text, sizeof(char), size_of_file, command_file);
    for(int i = 0; i < size_of_file; ++i){
        if(command_text[i] == ' ') number_of_commands++;
    }

    try {
        if (command_text == nullptr)    throw "zero pointer";
        if (number_of_commands++ == 0)  throw "file is empty";
    } catch (const char* exception) {
        fprintf(stderr, "Error: %s\n", exception);
    }

    simple_string* str_array = (simple_string*) calloc(number_of_commands, sizeof(simple_string));
    str_array[0].string = command_text;

    Arrange_string_ptrs(str_array, number_of_commands, command_text);

    *number_of_cmds = number_of_commands;

    return str_array;
}









#endif //PROC_ONEGIN_H
