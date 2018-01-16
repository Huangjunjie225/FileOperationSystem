#include <stdio.h>
#include <stdlib.h>
#include "empty_block.h"
#define getpch(type) (type*)malloc(sizeof(type))

void init_disk_block()
{
    int i,j;
    DB* tempDB;
    ADB = (DB*)malloc(sizeof(DB)*M*N);
    memset(ADB,'\0',sizeof(DB)*M*N);

    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            ADB[i*N + j].use = 0;
            ADB[i*N + j].num = i*N + j;
        }
    }
}

DB* findEmptyBlock()
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(ADB[i*N + j].use == 0)
            {
                return &ADB[i*N + j];
            }
        }
    }
    return NULL;
}

DB* write_disk_block(char *context)
{
    int index = 0,left_len;
    DB *empty_block,*pre_block,*first_block = NULL;
    if(context == NULL)
    {
        printf("\n");
        return NULL;
    }
    else
    {
        left_len = strlen(context);
        empty_block = findEmptyBlock();
        first_block = empty_block;
        pre_block = empty_block;
        empty_block->use = 1;
        empty_block->length = (left_len-BLOCK_SIZE+1 >= 0 ? BLOCK_SIZE-1:left_len);
        left_len = left_len - BLOCK_SIZE + 1;
        empty_block->context = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        strncpy(empty_block->context,context+index,BLOCK_SIZE-1);
        index += 7;
        while(left_len > 0)
        {
            empty_block = findEmptyBlock();
            pre_block->next_block = empty_block;
            empty_block->use = 1;
            empty_block->length = (left_len-BLOCK_SIZE+1 >= 0 ? BLOCK_SIZE-1:left_len);
            left_len = left_len - BLOCK_SIZE + 1;
            empty_block->context = (char*)malloc(sizeof(char)*BLOCK_SIZE);
            strncpy(empty_block->context,context+index,BLOCK_SIZE-1);
            index += 7;
            pre_block = empty_block;
        }
    }
    return first_block;
}

void free_disk_block(DB * first_disk_block)
{
    DB *temp_disk_block = NULL,*next_disk_block;
    temp_disk_block = first_disk_block;
    if(first_disk_block != NULL)
        next_disk_block = first_disk_block->next_block;
    while(temp_disk_block != NULL)
    {
        free(temp_disk_block->context);
        temp_disk_block->context = NULL;
        temp_disk_block->length = 0;
        temp_disk_block->use = 0;
        temp_disk_block = next_disk_block;
        next_disk_block = temp_disk_block->next_block;
    }
}
