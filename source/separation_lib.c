#include "separation_lib.h"



//-----------------------------------------------------------------------------
// Static functions prototypes
//-----------------------------------------------------------------------------

static string_info*
ReadFile (const char* const filename);


static size_t
GetFileSize (FILE* const file);


static size_t
GetStringsNumber (string_info* const text,
                  const char separator);


static string_info**
MakeSeparation (string_info* const text,
                const char separator,
                const size_t strings_num);

static text_separation*
TextSeparationConstructor (string_info* const text,
                           const char separator,
                           string_info** const strings_array,
                           const size_t strings_num);


static text_separation*
AbortSeparation (string_info* const text,
                 string_info** const strings_array,
                 const size_t strings_num);


static string_info*
BufferDestructor (string_info* const text);


static string_info**
StringsArrayDestructor (string_info** const strings_array,
                        const size_t strings_num);


static string_info*
StringInfoConstructor (char* const begin_ptr,
                       const size_t chars_number);


static string_info*
StringInfoDestructor (string_info* const string);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Interface functions implementation
//-----------------------------------------------------------------------------

text_separation*
SeparateTextFile (const char* const filename,
                  const char separator)
{
    text_separation* text_sep      = NULL;
    string_info*     buffer        = NULL;
    string_info**    strings_array = NULL;
    size_t           strings_num   = 0;

    buffer = ReadFile (filename);
    if (buffer == NULL)
        return AbortSeparation (buffer, strings_array, strings_num);

    strings_num = GetStringsNumber (buffer, separator);

    strings_array = MakeSeparation (buffer, separator, strings_num);
    if (strings_array == NULL)
        return AbortSeparation (buffer, strings_array, strings_num);

    text_sep = TextSeparationConstructor (buffer, separator,
                                          strings_array, strings_num);
    if (text_sep == NULL)
        return AbortSeparation (buffer, strings_array, strings_num);

    return text_sep;
}


text_separation*
DestroySeparation (text_separation* const text_sep)
{
    if (text_sep == NULL) return NULL;

    text_sep->text           = BufferDestructor       (text_sep->text);
    text_sep->strings_array  = StringsArrayDestructor (text_sep->strings_array,
                                                       text_sep->strings_number);
    text_sep->strings_number = 0;
    text_sep->separator      = '\0';

    free (text_sep);
    return NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Static functions implementation
//-----------------------------------------------------------------------------

static string_info*
ReadFile (const char* const filename)
{
    if (filename == NULL) return NULL;

    FILE* file = fopen (filename, "rb");
    if (file == NULL) return NULL;

    const size_t file_size = GetFileSize (file);
    if (file_size == 0)
    {
        fclose (file);
        return NULL;
    }

    char* buffer = malloc (file_size);
    if (buffer == NULL)
    {
        fclose (file);
        return NULL;
    }

    fread (buffer, sizeof (char), file_size, file);
    fclose (file);

    string_info* text = StringInfoConstructor (buffer, file_size);
    if (text == NULL) free (buffer);

    return text;
}


static size_t
GetFileSize (FILE* const file)
{
    assert (file);

    fseek (file, 0, SEEK_END);
    const size_t file_size = ftell (file);
    fseek (file, 0, SEEK_SET);

    return file_size;
}


static size_t
GetStringsNumber (string_info* const text,
                  const char separator)
{
    assert (text);

    const size_t char_num = text->chars_number;
    const char* const buffer = text->begin_ptr;

    size_t strings_num = 1;
    for (size_t i = 0; i < char_num; ++i)
    {
        if (buffer[i] == separator)
            ++strings_num;
    }

    if (char_num > 0 && buffer[char_num - 1] == separator)
        --strings_num;

    return strings_num;
}


static string_info**
MakeSeparation (string_info* const text,
                const char separator,
                const size_t strings_num)
{
    assert (text);

    string_info** strings_array = calloc (strings_num, sizeof (string_info*));
    if (strings_array == NULL) return NULL;

    const size_t char_num = text->chars_number;
    char* const buffer = text->begin_ptr;

    char*  cur_string_begin = buffer;
    size_t cur_string_index = 0;
    size_t cur_string_size  = 1;

    for (size_t i = 0; i < char_num; ++i)
    {
        if (buffer[i] == separator || i + 1 == char_num)
        {
            strings_array[cur_string_index] =
                StringInfoConstructor (cur_string_begin, cur_string_size);
            if (strings_array[cur_string_index] == NULL)
                return StringsArrayDestructor (strings_array, strings_num);

            ++cur_string_index;
            cur_string_begin = buffer + i + 1;
            cur_string_size  = 1;
        }

        else ++cur_string_size;
    }

    return strings_array;
}


static text_separation*
TextSeparationConstructor (string_info* const text,
                           const char separator,
                           string_info** const strings_array,
                           const size_t strings_num)
{
    assert (text);
    assert (strings_array);

    text_separation* text_sep = malloc (sizeof (text_separation));
    if (text_sep == NULL) return NULL;

    text_sep->text           = text;
    text_sep->strings_array  = strings_array;
    text_sep->strings_number = strings_num;
    text_sep->separator      = separator;

    return text_sep;
}


static text_separation*
AbortSeparation (string_info* const text,
                 string_info** const strings_array,
                 const size_t strings_num)
{
    BufferDestructor (text);
    StringsArrayDestructor (strings_array, strings_num);

    return NULL;
}


static string_info*
BufferDestructor (string_info* const text)
{
    if (text == NULL) return NULL;

    free (text->begin_ptr);
    return StringInfoDestructor (text);
}


static string_info**
StringsArrayDestructor (string_info** const strings_array,
                        const size_t strings_num)
{
    if (strings_array == NULL) return NULL;

    for (size_t i = 0; i < strings_num; ++i)
        strings_array[i] = StringInfoDestructor (strings_array[i]);

    free (strings_array);
    return NULL;
}


static string_info*
StringInfoConstructor (char* const begin_ptr,
                       const size_t chars_number)
{
    string_info* const string = malloc (sizeof (string_info));
    if (string == NULL) return NULL;

    string->begin_ptr    = begin_ptr;
    string->chars_number = chars_number;

    return string;
}


static string_info*
StringInfoDestructor (string_info* const string)
{
    if (string == NULL) return NULL;

    string->begin_ptr    = NULL;
    string->chars_number = 0;
    free (string);

    return NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
