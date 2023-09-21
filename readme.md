# FileOpenLibrary
### From [SeveraTheDuck](https://github.com/SeveraTheDuck)

This program opens file and reads it's input into a string (buffer).<br>
It fills struct named with buffer, its length, number of lines <br>
and (optional) array of strings.

### Guide for using the library

1. Initialize struct type of file_input and call for <br>
```GetFileInput(const char* file_name, struct file_input* buffer_info,```<br>
```             enum partition is_parted);``` <br>
    function. Include file_name of file you want to read from, pointer to your struct<br>
    and partition. Partition equals to ```PARTED``` if you want to part your buffer<br>
    and ```NOT_PARTED``` if not.
2. You get your struct filled with information. Use it as you like.
3. When the time has come to end the life of the struct, use <br>
```FreeFileInput(struct file_input* buffer_info);```<br>
