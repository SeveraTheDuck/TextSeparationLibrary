# FileOpenLibrary
### From [SeveraTheDuck](https://github.com/SeveraTheDuck)

This program opens file and reads it's input into a string (buffer).\
It fills struct named with buffer, its length, number of lines \
and (optional) array of strings.

### Guide for using the library

1. Initialize struct type of file_input and call for <br>
```GetFileInput(const char* file_name, struct file_input* buffer_info,```<br>
```             enum partition is_parted);``` <br>
    function. Include file_name of file you want to read from, pointer to your struct\
    and partition. Partition equals to ```PARTED``` if you want to part your buffer\
    and ```NOT_PARTED``` if not.
2.
