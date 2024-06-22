#pragma once



#include <stdlib.h>



//-----------------------------------------------------------------------------
// Text separation structures
//-----------------------------------------------------------------------------

/**
 * @brief String structure
 *
 * @note The string might be not null terminated
 */
typedef
struct string_info
{
    const char* begin_ptr;  ///< begin of string
    size_t chars_number;    ///< number of characters
}
string_info;


/**
 * @brief Structure which contains text and its separation information
 *
 * @details String_info structures contain pointers to the text
 */
typedef
struct text_separation
{
    char* text;                     ///< buffer with whole text
    char separator;                 ///< separator character
    string_info** strings_array;    ///< array of strings
    size_t strings_number;          ///< number of strings
}
text_separation;


/**
 * @brief Enumeration of possible error statuses
 */
enum separation_errors
{
    SEPARATION_SUCCESS = 0, ///< no error occured, success
    SEPARATION_ERROR   = 1  ///< error occured (allocation, nullptr etc)
};


/**
 * @brief Type to contatin error status
 */
typedef size_t separation_error_t;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Text separation interface
//-----------------------------------------------------------------------------

/**
 * @brief Opens file and separates its text into strings, closes file
 *
 * @param filename Name of file to separate
 * @param separator Separation character
 *
 * @retval Pointer to the text_separation structure
 * @retval NULL if allocation error occured
 * @retval NULL if file open  error occured
 *
 * @details This function opens file with name filename and makes an array
 * of strings
 *
 * @note The strings are not guaranteed to be null terminated
 */
text_separation*
SeparateTextFile (const char* const restrict filename,
                  const char separator);

/**
 * @brief Destructor for text_separation structure
 *
 * @param text_sep Pointer to the text_separation structure
 *
 * @retval NULL
 *
 * @details Frees memory of text buffer, strings_array and text_separation
 * structure itself
 */
text_separation*
DestroySeparation (text_separation* const text_sep);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
