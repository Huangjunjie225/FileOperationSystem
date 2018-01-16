#ifndef __FILE_H_
#define __FILE_H_
#include <stdio.h>
#include <string.h>

struct file
{
    unsigned int user_id;
    char *name;
    char *passwd;
    time_t create_time;
    struct user* next_user;
} *Users;

typedef struct user User;

void init_user();
User* login(char *name,char *passwd);
int add_user(char *name,char *passwd);
int delete_user(char *name);
void show_users();
#endif // __FILE_H_

