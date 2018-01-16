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
    unsigned int type;// 1-�ļ� 2-Ŀ¼
    char *file_name;//�ļ���
    DB* head_file_disk;//��һ���̿��ַ
    unsigned int file_len;//�ļ�����
    int own_user_id;//ӵ����id
    char* own_user_name;
    int own_pri;//ӵ����Ȩ�� 0 1 2 3 4 5 6 7
    int group_pri;//��Ȩ�� 0 1 2 3 4 5 6 7
    int others_pri;//����Ȩ�� 0 1 2 3 4 5 6 7
    time_t create_time;
    int status;//�ļ�״̬ 1-δ�� 2 �Ѵ�
    int open_file_user_id;//�򿪵��û���id Ĭ��Ϊ0
    struct my_file *pre_my_file;//��ǰĿ¼
    struct my_file *next_my_file;//�¼�Ŀ¼
    struct my_file *bro_my_file;//ͬ��Ŀ¼�е���һ��
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
