#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "struct_type.h"
#include "empty_block.h"
#include "user.h"
#include "my_file.h"
#define COLUMN 16
#define ROW 16

int main()
{
    char* testIN;
    char* operation;
    char context[100];
    char temp_context[100];
    char name[20];
    char passwd[20];
    User* cur_user;

    init_disk_block();
    init_user();
    init_my_file();

    do
    {
        printf("login as: ");
        gets(name);
        printf("%s@localhost's password: ",name);
        gets(passwd);
        while((cur_user = login(name,passwd)) == NULL && strcmp(passwd,"exit") != 0)
        {
            printf("Access denied\n");
            printf("%s@localhost's password: ",name);
            gets(passwd);
        }
    } while(cur_user == NULL || strcmp(passwd,"exit") == 0);
    printf("Welcome to Ubuntu!\n");
    do {
        printf("%s@localhost:%s$ ",cur_user->name,cur_user->cur_path);
        gets(context);
        if(strcmp(context,"logout") == 0)
        {
            logout(cur_user);
            cur_user = NULL;
            printf("success logout!\n");
            do
            {
                printf("login as: ");
                gets(name);
                printf("%s@localhost's password: ",name);
                gets(passwd);
                while((cur_user = login(name,passwd)) == NULL && strcmp(passwd,"exit") != 0)
                {
                    printf("Access denied\n");
                    printf("%s@localhost's password: ",name);
                    gets(passwd);
                }
            } while(cur_user == NULL || strcmp(passwd,"exit") == 0);
        }
        if(strcmp(context,"pwd") == 0)
        {
            centre_control(context,cur_user);
        }
        else if(start_cd(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_mkdir(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_ls(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_write(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_create(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_read(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_open(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_close(context) == 1)
        {
            centre_control(context,cur_user);
        }
        else if(start_delete(context) == 1)
        {
            centre_control(context,cur_user);
        }
        /**
        else if(user_add_command(context) == 1)
        {
            user_add(context,cur_user);
        }
        **/
    } while(strcmp("exit",context));

    printf("exit!");

    return 0;
}

