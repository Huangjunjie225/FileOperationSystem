#ifndef __USER_H_
#define __USER_H_
#include <stdio.h>
#include "struct_type.h"

int MAX_ID;
int add_user_command(char *context);
void init_user();
User* login(char *name,char *passwd);
int add_user(char *command,User *cur_user);
int delete_user(char *name);
void show_users();
#endif // __USER_H_
