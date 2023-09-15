#include "filestruct.h"
#include <string.h>
int main(int /*argc*/, char** /*argv*/)
{
    struct file_input buffer_info = {.buffer = NULL, .buffer_size = 0,
                                     .number_of_lines = 0,
                                     .lines_array = NULL};
    GetFileInput("input.txt", &buffer_info, PARTED);

    for(size_t i = 0; i < buffer_info.number_of_lines; ++i)
    {
        printf("%s ",  buffer_info.lines_array[i].line);
    }

    FreeFileInput(&buffer_info);
    return 0;
}
