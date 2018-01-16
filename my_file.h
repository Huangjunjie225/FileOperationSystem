#ifndef __MY_FILE_H_
#define __MY_FILE_H_
#include <stdio.h>
#include <string.h>
#include "struct_type.h"

MF* ROOT_FILE;
int MAX_FILE_ID;

void centre_control(char *command,User *cur_user);
void init_my_file();

#endif // __MY_FILE_H_
