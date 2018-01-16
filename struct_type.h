#ifndef __STRUCT_TYPE_H_
#define __STRUCT_TYPE_H_
#include <stdio.h>
#include <string.h>

struct disk_block {
    unsigned int num;
    unsigned int use;
    unsigned int length;
    char* context;
    struct disk_block *next_block;
}*ADB;

typedef struct disk_block DB;

struct my_file
{
    unsigned int file_id;
    unsigned int type;// 1-文件 2-目录
    char *file_name;//文件名
    DB* head_file_disk;//第一个盘块地址
    unsigned int file_len;//文件长度
    int own_user_id;//拥有者id
    char* own_user_name;
    int own_pri;//拥有者权限 0 1 2 3 4 5 6 7
    int group_pri;//组权限 0 1 2 3 4 5 6 7
    int others_pri;//其他权限 0 1 2 3 4 5 6 7
    time_t create_time;
    int status;//文件状态 1-未打开 2 已打开
    int open_file_user_id;//打开的用户的id 默认为0
    struct my_file *pre_my_file;//先前目录
    struct my_file *next_my_file;//下级目录
    struct my_file *bro_my_file;//同级目录中的下一个
} *My_File;

typedef struct my_file MF;

struct user
{
    unsigned int user_id;
    char *name;
    char *passwd;
    char *cur_path;
    time_t create_time;
    struct MF* cur_directory;
    struct user* next_user;
} *Users;

typedef struct user User;

#endif // __STRUCT_TYPE_H_
