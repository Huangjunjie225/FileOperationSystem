#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "my_file.h"
#include "struct_type.h"

char* convert_command(char *command)
{
    char temp[100];
    char *result;
    int i,j,is_blank;
    i = 0,j = 0;
    is_blank = 0;
    while(*(command+i)!='\0')
    {
        if(*(command+i) == ' ' && is_blank == 1)
        {
            i++;
        }
        else if(*(command+i) == ' ')
        {
            temp[j] = *(command+i);
            j++;
            i++;
            is_blank = 1;
        }
        else
        {
            temp[j] = *(command+i);
            is_blank = 0;
            i++;
            j++;
        }
    }
    temp[j] = '\0';
    result = (char*)malloc((sizeof(char)*strlen(temp) + 1));
    memcpy(result,temp,(sizeof(char)*strlen(temp) + 1));
    return result;
}

int start_cd(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 2 && *(context) == 'c' && *(context+1) == 'd')
    {
        return 1;
    }
    return 0;
}

int start_ls(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) >= 2 && *(context) == 'l' && *(context+1) == 's')
    {
        return 1;
    }
    return 0;
}

int start_mkdir(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 5 && *(context) == 'm' && *(context+1) == 'k'
       && *(context+2) == 'd'
       && *(context+3) == 'i'
       && *(context+4) == 'r')
    {
        return 1;
    }
    return 0;
}


int start_write(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 5 && *(context) == 'w' && *(context+1) == 'r'
       && *(context+2) == 'i'
       && *(context+3) == 't'
       && *(context+4) == 'e')
    {
        return 1;
    }
    return 0;
}

int start_create(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 6 && *(context) == 'c' && *(context+1) == 'r'
       && *(context+2) == 'e'
       && *(context+3) == 'a'
       && *(context+4) == 't'
       && *(context+5) == 'e')
    {
        return 1;
    }
    return 0;
}

int start_read(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 4 && *(context) == 'r' && *(context+1) == 'e'
       && *(context+2) == 'a'
       && *(context+3) == 'd')
    {
        return 1;
    }
    return 0;
}

int start_open(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 4 && *(context) == 'o' && *(context+1) == 'p'
       && *(context+2) == 'e'
       && *(context+3) == 'n')
    {
        return 1;
    }
    return 0;
}

int start_close(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 5 && *(context) == 'c' && *(context+1) == 'l'
       && *(context+2) == 'o'
       && *(context+3) == 's'
       && *(context+4) == 'e')
    {
        return 1;
    }
    return 0;
}

int start_delete(char *context)
{
    char * convert;
    convert = convert_command(context);
    if(strlen(convert) > 6 && *(context) == 'd' && *(context+1) == 'e'
       && *(context+2) == 'l'
       && *(context+3) == 'e'
       && *(context+4) == 't'
       && *(context+5) == 'e')
    {
        return 1;
    }
    return 0;
}


void init_my_file()
{
    MF* home_file;
    MAX_FILE_ID = 1;
    ROOT_FILE = (MF*)malloc(sizeof(MF));
    ROOT_FILE->file_id = 1;
    ROOT_FILE->file_len = 0;
    ROOT_FILE->type = 2;
    ROOT_FILE->file_name = (char*)malloc(sizeof(char)*100);
    strcpy(ROOT_FILE->file_name,"/");
    ROOT_FILE->group_pri = 0;
    ROOT_FILE->others_pri = 0;
    ROOT_FILE->own_pri = 0;
    ROOT_FILE->own_user_id = Users->user_id;
    ROOT_FILE->pre_my_file = NULL;
    ROOT_FILE->head_file_disk = NULL;
    ROOT_FILE->create_time = time(NULL);
    ROOT_FILE->next_my_file = NULL;
    ROOT_FILE->bro_my_file = NULL;
    ROOT_FILE->own_user_name = (char*)malloc(sizeof(char)*50);
    ROOT_FILE->status = 0;
    ROOT_FILE->open_file_user_id = 0;
    strcpy(ROOT_FILE->own_user_name,Users->name);

    home_file = (MF*)malloc(sizeof(MF));
    home_file->file_id = ++MAX_FILE_ID;
    home_file->file_len = 0;
    home_file->create_time = time(NULL);
    home_file->file_name = (char*)malloc(sizeof(char)*100);
    strcpy(home_file->file_name,"home");
    home_file->group_pri = 0;
    home_file->own_pri = 0;
    home_file->others_pri = 0;
    home_file->head_file_disk = NULL;
    home_file->bro_my_file = NULL;
    home_file->next_my_file = NULL;
    home_file->pre_my_file = ROOT_FILE;
    home_file->type = 2;
    home_file->own_user_name = (char*)malloc(sizeof(char)*50);
    strcpy(home_file->own_user_name,Users->name);
    home_file->status = 0;
    home_file->open_file_user_id = 0;
    ROOT_FILE->next_my_file = home_file;
}

char* get_cur_path(User *cur_user)
{
    return cur_user->cur_path;
}

//中央控制路由
void centre_control(char *command,User *cur_user)
{
    char temp[100];
    char *convert = NULL;
    if(command == NULL) return;
    convert = convert_command(command);
    if(strcmp("pwd",convert)==0)
    {
        printf("%s\n",cur_user->cur_path);
    }
    else if(start_cd(convert) == 1)
    {
        cd_file(convert,cur_user);
    }
    else if(start_ls(convert) == 1)
    {
        list_file(cur_user);
    }
    else if(start_mkdir(convert) == 1)
    {
        mkdir(convert,cur_user);
    }
    else if(start_write(convert) == 1)
    {
        write_file(convert,cur_user);
    }
    else if(start_create(convert) == 1)
    {
        create_file(convert,cur_user);
    }
    else if(start_read(convert) == 1)
    {
        read_file(convert,cur_user);
    }
    else if(start_open(convert) == 1)
    {
        open_file(convert,cur_user);
    }
    else if(start_close(convert) == 1)
    {
        close_file(convert,cur_user);
    }
    else if(start_delete(convert) == 1)
    {
        delete_file(convert,cur_user);
    }
}


int find_last_delim_index(char* s,char delim)
{
    int index = -1,count = 0,i;
    i = strlen(s);
    while(i >= 0)
    {
        if(*(s+i) == delim)
        {
            count++;
            if(count == 2)
            {
                return i;
            }
        }
        i--;
    }
    return -1;
}

void cd_file(char *command,User *cur_user)
{
    char delims[] = " ";
    char directory_delims[] = "/";
    char *result;
    char *path = NULL;
    int command_count = 0,index,error = 0;
    MF *temp_directory = NULL;
    MF *next_directory = NULL;
    MF *bro_directory = NULL;
    MF *pre_directory = NULL;
    MF *cur_directory = cur_user->cur_directory;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: cd:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }
    if(*(path) == '/')
    {
        cur_user->cur_directory = ROOT_FILE;
        strcpy(cur_user->cur_path,"/");
        result = strtok(path,directory_delims);

        next_directory = ROOT_FILE->next_my_file;
        pre_directory = cur_user->cur_directory;

        do
        {
            if(next_directory != NULL && next_directory->type == 2 && strcmp(result,next_directory->file_name) == 0)
            {
                cur_user->cur_directory = next_directory;
                next_directory = next_directory->next_my_file;
                strcat(cur_user->cur_path,result);
                strcat(cur_user->cur_path,"/");
            }
            else if(next_directory != NULL)
            {
                bro_directory = next_directory->bro_my_file;
                while(bro_directory != NULL)
                {
                    if(strcmp(result,bro_directory->file_name) == 0 && bro_directory->type == 2)
                    {
                        cur_user->cur_directory = bro_directory;
                        next_directory = bro_directory->next_my_file;
                        strcat(cur_user->cur_path,result);
                        strcat(cur_user->cur_path,"/");
                        break;
                    }
                    bro_directory = bro_directory->bro_my_file;
                }
                if(bro_directory == NULL)
                {
                    error = 1;
                    break;
                }
            }
            else
            {
                error = 1;
                break;
            }
            if(error == 0)
            {
                result = strtok(NULL,directory_delims);
            }
        } while(result != NULL && error == 0);
    }
    else
    {
        result = strtok(path,directory_delims);
        while(result != NULL)
        {
            if(strcmp("..",result) == 0)
            {
                index = find_last_delim_index(cur_user->cur_path,'/');
                if(index != -1)
                {
                    strncpy(cur_user->cur_path,cur_user->cur_path,index+1);
                    *(cur_user->cur_path+index+1) = '\0';
                    cur_user->cur_directory = ((MF*)cur_user->cur_directory)->pre_my_file;
                }
                else
                {
                    printf("error!\n");
                    break;
                }
            }
            else if(strcmp(".",result) != 0)
            {
                next_directory = cur_directory->next_my_file;

                if(next_directory != NULL && next_directory->type == 2 && strcmp(result,next_directory->file_name) == 0)
                {
                    cur_user->cur_directory = next_directory;
                    next_directory = next_directory->next_my_file;
                    strcat(cur_user->cur_path,result);
                    strcat(cur_user->cur_path,"/");
                }
                else if(next_directory != NULL)
                {
                    bro_directory = next_directory->bro_my_file;
                    while(bro_directory != NULL)
                    {
                        if(strcmp(result,bro_directory->file_name) == 0 && bro_directory->type == 2)
                        {
                            cur_user->cur_directory = bro_directory;
                            next_directory = bro_directory->next_my_file;
                            strcat(cur_user->cur_path,result);
                            strcat(cur_user->cur_path,"/");
                            break;
                        }
                        bro_directory = bro_directory->bro_my_file;
                    }
                    if(bro_directory == NULL)
                    {
                        error = 1;
                        break;
                    }
                }
                else
                {
                    error = 1;
                    break;
                }
            }
            result = strtok(NULL,directory_delims);
        }
    }
    if(error == 1)
    {
        printf("error! no such directory!\n");
    }
}

void find_make_directory(char *path,User *cur_user)
{
    char temp_path[100];
    char *result;
    int index,is_found=0,is_create=0;
    char directory_delims[] = "/";
    MF *temp_directory = NULL;
    MF *next_directory = NULL;
    MF *bro_directory = NULL;
    MF *pre_directory = NULL;
    MF *cur_directory = cur_user->cur_directory;

    if(*(path) == '/') temp_directory = ROOT_FILE;
    else temp_directory = cur_directory;

    next_directory = temp_directory->next_my_file;
    pre_directory = temp_directory;
    do
    {
        result = strtok(path,directory_delims);
        if(result == NULL)
        {
            printf("file had been created!\n");
            is_create = 1;
            break;
        }
        if(strcmp(".",result) == 0)
        {
            result = strtok(NULL,directory_delims);
        }
        if(next_directory != NULL && next_directory->type == 2 && strcmp(result,next_directory->file_name) == 0)
        {
            pre_directory = next_directory;
            next_directory = next_directory->next_my_file;
        }
        else if(next_directory != NULL)
        {
            bro_directory = next_directory->bro_my_file;
            while(bro_directory != NULL)
            {
                if(strcmp(result,bro_directory->file_name) == 0 && bro_directory->type == 2)
                {
                    pre_directory = next_directory;
                    next_directory = bro_directory->next_my_file;
                    break;
                }
                bro_directory = bro_directory->bro_my_file;
            }
            if(bro_directory == NULL)
            {
                next_directory = NULL;
            }
        }
    } while(next_directory != NULL);
    //已经在现有的目录中找不到找不到了
    if(is_create == 0)
    {
        temp_directory = (MF*)malloc(sizeof(MF));
        temp_directory->create_time = time(NULL);
        temp_directory->file_id = ++MAX_FILE_ID;
        temp_directory->file_len = 0;
        temp_directory->type = 2;
        temp_directory->file_name = (char *)malloc(sizeof(char)*50);
        strcpy(temp_directory->file_name,result);
        temp_directory->group_pri = 1;
        temp_directory->head_file_disk = NULL;
        temp_directory->next_my_file = NULL;
        temp_directory->others_pri = 0;
        temp_directory->own_pri = 7;
        temp_directory->pre_my_file = pre_directory;
        temp_directory->bro_my_file = NULL;
        temp_directory->own_user_id = cur_user->user_id;
        temp_directory->own_user_name = (char*)malloc(sizeof(char)*50);
        strcpy(temp_directory->own_user_name,cur_user->name);
        temp_directory->status = 0;
        temp_directory->open_file_user_id = 0;
        bro_directory = pre_directory->next_my_file;
        if(bro_directory == NULL)
        {
            pre_directory->next_my_file = temp_directory;
        }
        else
        {
            while(bro_directory->bro_my_file != NULL)
            {
                bro_directory = bro_directory->bro_my_file;
            }
            bro_directory->bro_my_file = temp_directory;
        }
        pre_directory = temp_directory;
        result = strtok(NULL,directory_delims);
        while(result != NULL)
        {
            temp_directory = (MF*)malloc(sizeof(MF));
            temp_directory->create_time = time(NULL);
            temp_directory->file_id = ++MAX_FILE_ID;
            temp_directory->file_len = 0;
            temp_directory->type = 2;
            temp_directory->file_name = (char *)malloc(sizeof(char)*50);
            strcpy(temp_directory->file_name,result);
            temp_directory->group_pri = 1;
            temp_directory->head_file_disk = NULL;
            temp_directory->next_my_file = NULL;
            temp_directory->others_pri = 0;
            temp_directory->own_pri = 7;
            temp_directory->pre_my_file = pre_directory;
            temp_directory->bro_my_file = NULL;
            temp_directory->own_user_id = cur_user->user_id;
            temp_directory->own_user_name = (char*)malloc(sizeof(char)*50);
            strcpy(temp_directory->own_user_name,cur_user->name);
            temp_directory->status = 0;
            temp_directory->open_file_user_id = 0;
            bro_directory = pre_directory->next_my_file;
            if(bro_directory == NULL) pre_directory->next_my_file = temp_directory;
            else
            {
                while(bro_directory->bro_my_file != NULL)
                {
                    bro_directory = bro_directory->bro_my_file;
                }
                bro_directory->bro_my_file = temp_directory;
            }
            pre_directory = temp_directory;
            result = strtok(NULL,directory_delims);
        }
    }
}

void mkdir(char *command,User *cur_user)
{
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: mkdir:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }
    find_make_directory(path,cur_user);
}

void list_file(User *cur_user)
{
    MF *cur_directory = cur_user->cur_directory;
    MF *bro_directory = cur_directory->next_my_file;
    MF *pre_directory = cur_directory->pre_my_file;
    printf("%d %s %s %d \n",cur_directory->file_id,".",cur_directory->own_user_name,0);
    if(cur_directory->file_id == 1)
    {
        printf("%d %s %s %d \n",0,"..","root",0);
    }
    else
    {
        printf("%d %s %s %d \n",pre_directory->file_id,"..",pre_directory->own_user_name,0);
    }
    while(bro_directory != NULL)
    {
        printf("%d %s %s %d \n",bro_directory->file_id,bro_directory->file_name,bro_directory->own_user_name,bro_directory->file_len);
        bro_directory = bro_directory->bro_my_file;
    }
}

MF* get_my_file(char *path,User *cur_user)
{
    MF *temp_directory = NULL;
    MF *next_directory = NULL;
    MF *bro_directory = NULL;
    MF *cur_directory = cur_user->cur_directory;
    char temp_path[100];
    char directory_delims[] = "/";
    char *result;
    int error = 0;

    next_directory = cur_directory;
    strcpy(temp_path,cur_user->cur_path);
    result = strtok(path,directory_delims);

    while(result != NULL)
    {
        if(strcmp("..",result) == 0)
        {
            next_directory = next_directory->pre_my_file;
        }
        else if(strcmp(".",result) != 0)
        {
            if(next_directory != NULL && strcmp(result,next_directory->file_name) == 0)
            {
                temp_directory = next_directory;
                next_directory = next_directory->next_my_file;
            }
            else if(next_directory != NULL)
            {
                bro_directory = next_directory->next_my_file;
                while(bro_directory != NULL)
                {
                    if(strcmp(result,bro_directory->file_name) == 0)
                    {
                        temp_directory = bro_directory;
                        next_directory = bro_directory->next_my_file;
                        break;
                    }
                    bro_directory = bro_directory->bro_my_file;
                }
                if(bro_directory == NULL)
                {
                    error = 1;
                    break;
                }
            }
            else
            {
                error = 1;
                break;
            }
        }
        result = strtok(NULL,directory_delims);
    }
    if(error == 0 && temp_directory != NULL && temp_directory->type == 1)
    {
        return temp_directory;
    }
    else return NULL;
}

/**
  *只能在当前目录下创建文件
  **/
void create_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    MF *cur_directory = cur_user->cur_directory;
    MF *new_file;
    MF *bro_file;
    int command_count = 0,index;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: create:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }
    new_file = (MF*)malloc(sizeof(MF));
    new_file->create_time = time(NULL);
    new_file->file_id = ++MAX_FILE_ID;
    new_file->file_len = 0;
    new_file->file_name = (char*)malloc(sizeof(char)*50);
    strcpy(new_file->file_name,path);
    new_file->group_pri = 0;
    new_file->head_file_disk = NULL;
    new_file->next_my_file = NULL;
    new_file->others_pri = 0;
    new_file->own_user_id = cur_user->user_id;
    new_file->own_user_name = (char*)malloc(sizeof(char)*50);
    strcpy(new_file->own_user_name,cur_user->name);
    new_file->status = 0;
    new_file->open_file_user_id = 0;
    new_file->pre_my_file = cur_user->cur_directory;
    new_file->type = 1;
    bro_file = ((MF*)(cur_user->cur_directory))->next_my_file;
    if(bro_file == NULL) ((MF*)(cur_user->cur_directory))->next_my_file = new_file;
    else
    {
        while(bro_file->bro_my_file != NULL)
        {
            bro_file = bro_file->bro_my_file;
        }
        bro_file->bro_my_file = new_file;
    }
}

void write_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    MF* writing_file = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: write:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }

    //printf("start find ...\n");
    writing_file = get_my_file(path,cur_user);//根据path找到对应的文件
    //printf("end find ...\n");
    if(writing_file->status == 1 && writing_file->open_file_user_id == cur_user->user_id)
    {
        printf("input:\n");
        gets(text);
        DB* first_disk_block = write_disk_block(text);
        writing_file->head_file_disk = first_disk_block;
        writing_file->file_len = strlen(text);
    }
    else
    {
        printf("file not open or file opened by others\n");
    }
}

void read_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    MF* writing_file = NULL;
    DB* temp_disk_block = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: read:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }

    writing_file = get_my_file(path,cur_user);//根据path找到对应的文件
    if(writing_file != NULL && (writing_file->status == 1 && writing_file->open_file_user_id == cur_user->user_id))
    {
        printf("output:\n");
        temp_disk_block = writing_file->head_file_disk;
        while(temp_disk_block != NULL)
        {
            printf("%s",temp_disk_block->context);
            temp_disk_block = temp_disk_block->next_block;
        }
        printf("\n");
    }
    else
    {
        printf("file not open or file opened by others\n");
    }
}


void open_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    MF* writing_file = NULL;
    DB* temp_disk_block = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: open:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }

    writing_file = get_my_file(path,cur_user);//根据path找到对应的文件
    if(writing_file != NULL)
    {
        writing_file->status = 1;
        writing_file->open_file_user_id = cur_user->user_id;
        printf("file opening!\n");
    }
}

void close_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    MF* writing_file = NULL;
    DB* temp_disk_block = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: close:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }

    writing_file = get_my_file(path,cur_user);//根据path找到对应的文件
    if(writing_file != NULL && writing_file->open_file_user_id == cur_user->user_id)
    {
        writing_file->status = 0;
        writing_file->open_file_user_id = 0;
        printf("file had been closed\n");
    }
}


void delete_file(char *command,User *cur_user)
{
    char text[100];
    char delims[] = " ";
    char *result;
    char *path = NULL;
    int command_count = 0,index;
    MF* writing_file = NULL;
    MF* pre_file = NULL;
    MF* next_file = NULL;
    MF* bro_file = NULL;
    DB* temp_disk_block = NULL;
    result = strtok(command,delims);
    while(result != NULL)
    {
        command_count++;
        if(command_count == 2)
        {
            path = result;
        }
        else if(command_count > 2)
        {
            printf("-bash: delete:%s no such directory\n",result);
            break;
        }
        result = strtok(NULL,delims);
    }

    writing_file = get_my_file(path,cur_user);//根据path找到对应的文件

    if(cur_user->user_id == writing_file->own_user_id)
    {
        pre_file = writing_file->pre_my_file;
        next_file = writing_file->next_my_file;
        if(next_file != NULL)
        {
            printf("under this directory has file! please remove its\n");
        }
        else
        {
            bro_file = pre_file->next_my_file;
            if(bro_file == writing_file)
            {
                pre_file->next_my_file = writing_file->bro_my_file;
                free(writing_file);
            }
            else
            {
                while(bro_file->bro_my_file != writing_file)
                {
                    bro_file = bro_file->bro_my_file;
                }
                bro_file->bro_my_file = writing_file->bro_my_file;
                free(writing_file);
            }

        }
    }
}

