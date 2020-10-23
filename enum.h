//
// Created by mikipaw on 16.10.2020.
//
#ifndef PROC_ENUM_H
#define PROC_ENUM_H



/*!@enum Commands
 * Commands with numbers from 0 to 14
 */
enum Commands{
#define DEF_CMD(name, num, code) CMD_##name = num,
#include "commands.h"
    end
#undef DEF_CMD
};


#endif //PROC_ENUM_H
