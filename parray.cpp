#include "parray.h"

// вопросы:
// вывод русских символов (не строк)
// выравнивание при приведении типов (char* -> size_t*, 1 -> 8)
//

// сделать:
// структуры
// пропускать знаки препинания (а пустые строки?)
// вынести компаратор
// подсчёт вхождений символа в буфере
//

// void PrintParray(char** pointer_array, size_t number_of_lines)
// {
//     for (size_t i = 0; i < number_of_lines; ++i)
//     {
//         printf("%s\n", pointer_array[i]);
//     }
//     return;
// }
//
// void MySwap(char** str1, char** str2)
// {
//     char* temp_str = *str1;
//     *str1 = *str2;
//     *str2 = temp_str;
//     return;
// }
//
// void SortStringsArray(char** pointer_array, size_t number_of_lines)
// {
//     int cmp_status = 0;
//     for (size_t i = 0; i < number_of_lines; ++i)
//     {
//         for (size_t j = 0; j < number_of_lines - i - 1; ++j)
//         {
//             cmp_status = strcmp(pointer_array[j], pointer_array[j + 1]);
//             if (cmp_status > 0) MySwap(&pointer_array[j], &pointer_array[j + 1]);
//         }
//     }
//     for (size_t i = 0; i < number_of_lines; ++i)
//     {
//         FILE* fp = fopen("sorted.txt", "a"); //?
//         assert(fp);
//
//         //fputs(pointer_array[i], fp);
//         fprintf(fp, "%s\n", pointer_array[i]);
//
//         fclose(fp);
//     }
//     return;
// }

size_t GetFileSize(FILE* fp)
{
    assert(fp);

    fseek(fp, 0, SEEK_END);
    size_t buffer_size = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return buffer_size;
}

char* MakeBuffer(size_t buffer_size)
{
    char* buffer = (char*)calloc(buffer_size + 1, sizeof(char));
    assert(buffer);

    return buffer;
}

void ReadFileToBuffer(const char* file_name, struct file_input* buffer_info)
{
    FILE* fp = fopen(file_name, "rb");
    assert(fp);

    buffer_info->buffer_size = GetFileSize(fp);
    buffer_info->buffer      = MakeBuffer(buffer_info->buffer_size);

    fread(buffer_info->buffer, sizeof(char), buffer_info->buffer_size, fp);

    fclose(fp);
    fp = NULL;

    return;
}

void GetNumberOfLines(struct file_input* buffer_info)
{
    assert(buffer_info->buffer);

    buffer_info->number_of_lines = 0;
    for (size_t buffer_index = 0; buffer_index < buffer_info->buffer_size; ++buffer_index)
    {
        if (buffer_info->buffer[buffer_index] == '\n')
        {
            ++(buffer_info->number_of_lines);
        }
    }

    if (buffer_info->buffer[buffer_info->buffer_size - 1] != '\n')
    {
        buffer_info->buffer[buffer_info->buffer_size]  = '\0';        // there're buffer_size + 1 elements, so it's
        ++(buffer_info->number_of_lines);                             // legal to call for buffer[buffer_size]
    }

    return;
}

void MakeArrayOfStrings(struct file_input* buffer_info)
{
    buffer_info->strings_array = (char**)calloc(buffer_info->number_of_lines, sizeof(char*));
    assert(buffer_info->strings_array);

    size_t current_line = 0;
    buffer_info->strings_array[current_line++] = buffer_info->buffer;

    for (size_t buffer_index = 0; buffer_index < buffer_info->buffer_size; ++buffer_index)
    {
        if (buffer_info->buffer[buffer_index] == '\n')
        {
            buffer_info->buffer[buffer_index] =  '\0';
            if (current_line < buffer_info->number_of_lines)
            {
                buffer_info->strings_array[current_line++] = buffer_info->buffer + buffer_index + 1;
            }
        }
    }

    return;
}

void FreeFileInput(struct file_input* buffer_info)
{
    free(buffer_info->buffer);
    buffer_info->buffer = NULL;

    if (buffer_info->strings_array)
    {
        free(buffer_info->strings_array);
        buffer_info->strings_array = NULL;
    }

    return;
}

void GetFileInput(const char* file_name, struct file_input* buffer_info,
                  enum partition is_separated)
{
    ReadFileToBuffer(file_name, buffer_info);
    GetNumberOfLines(buffer_info);

    if (is_separated)
    {
        MakeArrayOfStrings(buffer_info);
    }
    return;
}
