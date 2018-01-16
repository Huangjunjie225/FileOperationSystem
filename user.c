#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "my_file.h"
#define getpch(type) (type*)malloc(sizeof(type))

int add_user_command(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 7 && *(context) == 'u' && *(context+1) == 's'
       && *(context+2) == 'e'
       && *(context+3) == 'r'
       && *(context+4) == 'a'
       && *(context+5) == 'd'
       && *(context+6) == 'd')
    {
        return 1;
    }
    return 0;
}

void init_user()
{
    MAX_ID = 1;
    Users = (User *)malloc(sizeof(User));
    Users->user_id = 1;
    Users->name = "root";
    Users->passwd = "123456";
    Users->cur_path = (char*)malloc(sizeof(char)*100);
    strcpy(Users->cur_path,"/");
    Users->create_time = time(NULL);
    Users->next_user = NULL;
}

User* login(char* name,char* passwd)
{
    User* u;
    int i,j,found=0;
    u = Users;
    if(name == NULL || passwd == NULL) return NULL;
    while(u != NULL)
    {
        if(strcmp(name,u->name) == 0 && strcmp(passwd,u->passwd) == 0)
        {
            found = 1;
            if(strcmp("root",u->name) == 0)
            {
                u->cur_directory = ROOT_FILE;
            }
            else
            {
                //TODO 修改该用户当前目录
            }
            break;
        }
        u = u->next_user;
    }
    if(found == 1) return u;
    else return NULL;
}

int add_user(char *command,User *cur_user)
{
    User *u,*temp;
    char* name,* passwd;
    int found = 0;
    char text[100];
    char delims[] = " ";
    char *result;
    int command_count = 0,index;
    MF* writing_file = NULL;
    DB* temp_disk_block = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            name = result;
        }
        if(command_count == 3)
        {
            passwd = result;
        }
        else if(command_count > 3)
        {
            printf("-bash: write:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }
    u = Users;
    if(NULL == name || NULL == passwd) return -1;
    while(u != NULL)
    {
        if(strcmp(name,u->name)==0)
        {
            found = 1;
            strcat(u->cur_path,"/home/");
            strcat(u->cur_path,u->name);
            break;
        }
        u = u->next_user;
    }
    if(found == 1) {
        return 0;
    }
    else
    {
        u = (User *)malloc(sizeof(User));
        u->name = name;
        u->passwd = passwd;
        u->user_id = ++MAX_ID;
        u->create_time = time(NULL);
        u->next_user = NULL;
        temp = Users;
        while(temp->next_user != NULL)
        {
            temp = temp->next_user;
        }
        temp->next_user = u;
        return 1;
    }
}

int delete_user(char *name)
{
    User *u,*temp;
    int found = 0;
    u = Users;
    //如果用户链表只有一个用户并且正好是要删除的用户，则报错
    if(u->next_user == NULL && strcmp(name,u->name)==0)
    {
        return -1;
    }
    while(u->next_user != NULL)
    {
        if(strcmp(u->next_user->name,name)==0)
        {
            found = 1;
            temp = u->next_user;
            u->next_user = temp->next_user;
        }
        else
        {
            u = u->next_user;
        }
    }
    if(found == 1) return 1;
    else return -2;
}

void show_users()
{
    User *u;
    u = Users;
    while(u != NULL)
    {
        printf("%d:%s:%s:",u->user_id,u->name,u->passwd);
        printf(asctime(u->create_time));
        printf("\n");
        u = u->next_user;
    }
}

void logout(User *user)
{
    strcat(user->cur_path,"/home/");
    strcat(user->cur_path,user->name);
}
