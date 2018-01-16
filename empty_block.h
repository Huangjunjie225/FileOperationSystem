#ifndef __EMPTY_BLOCK_H_
#define __EMPTY_BLOCK_H_
#include <stdio.h>
#include "struct_type.h"
#define M 16
#define N 16
#define BLOCK_SIZE 8

void init_disk_block();
int testEmptyBlock(int row,int column);
DB* write_disk_block(char *context);

#endif // __EMPTY_BLOCK_H_
