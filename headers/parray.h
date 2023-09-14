#ifndef __PARRAY_H__
#define __PARRAY_H__

#include <stdio.h>
#include <assert.h>

enum partition
{
    NOT_PARTED = 0,
    PARTED     = 1,
};

struct file_input
{
    char* buffer;
    size_t buffer_size;
    size_t number_of_lines;
    char** strings_array = NULL;
};

size_t GetFileSize(FILE* fp);

char* MakeBuffer(size_t buffer_size);

void ReadFileToBuffer(const char* file_name, struct file_input* buffer_info);

void GetNumberOfLines(struct file_input* buffer_info);

void MakeArrayOfStrings(struct file_input* buffer_info);

void FreeFileInput(struct file_input* buffer_info);

void GetFileInput(const char* file_name, struct file_input* buffer_info,
                  enum partition is_parted);

#endif
