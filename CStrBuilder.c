
/*
 * File: CStrBuilder.c
 * Date: Jun 30, 2017
 * Name: Kevin Tyrrell
 * Version: 1.0.0
 */

/*
Copyright © 2017 Kevin Tyrrell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "CStrBuilder.h"

#define CSB_NULL_CHAR '\0'
#define CSB_SPACE_CHAR ' '
#define CSB_BUFFER_SIZE 1024 * 16

/* StringBuilder structure. */
struct CStrBuilder
{
    Vector *vect;
};

/*
 * Constructor function.
 * Θ(1)
 */
CStrBuilder* CStrBuilder_new()
{
    CStrBuilder* const builder = mem_malloc(sizeof(CStrBuilder));
    builder->vect = Vector_new(NULL, NULL);
    return builder;
}

/*
 * Returns the amount of characters in the String.
 * Θ(1)
 */
size_t csb_size(const CStrBuilder* const builder)
{
    io_assert(builder != NULL, IO_MSG_NULL_PTR);
    return vect_size(builder->vect);
}

/*
 * Appends the specified String to the builder.
 * The specified String must be terminated with a NULL character.
 * Θ(n)
 */
void csb_append(CStrBuilder* const builder, const char* const str)
{
    io_assert(builder != NULL, IO_MSG_NULL_PTR);
    io_assert(str != NULL, IO_MSG_NULL_PTR);

    for (unsigned int i = 0; str[i] != CSB_NULL_CHAR; i++)
    {
        char* const letter = mem_malloc(sizeof(char));
        *letter = str[i];
        vect_push_back(builder->vect, letter);
    }
}

/*
 * Appends data to the builder specified by the format and parameters.
 * The appended data would appear the same as the result of the printf(format, ...).
 * For more information on format specifiers, see documentation for printf.
 */
void csb_appendf(CStrBuilder *const builder, const char* format, ...)
{
    io_assert(builder != NULL, IO_MSG_NULL_PTR);

    char buffer[CSB_BUFFER_SIZE];
    va_list argptr;
    va_start(argptr, format);
    const int size = vsnprintf(buffer, CSB_BUFFER_SIZE - 1, format, argptr);
    va_end(argptr);

    vect_grow_to(builder->vect, vect_size(builder->vect) + size);
    csb_append(builder, buffer);
}

/*
 * Removes leading and trailing whitespace.
 * Ω(1), O(n)
 */
void csb_trim(CStrBuilder *const builder)
{
    io_assert(builder != NULL, IO_MSG_NULL_PTR);

    /* Get and pop for front and back. */
    void* (*gets[2])(const Vector*) = { &vect_front, &vect_back };
    void (*pops[2])(Vector*) = { &vect_pop_front, &vect_pop_back };

    char *letter;
    for (int i = 0; i < 2; i++)
        while (!vect_empty(builder->vect) && *(letter = gets[i](builder->vect)) == CSB_SPACE_CHAR)
        {
            pops[i](builder->vect);
            mem_free(letter, sizeof(char));
        }
}

/*
 * De-constructs the builder and returns its contents as a NULL terminated String.
 * The returned array will have the size of n + 1 and must be de-allocated after use.
 * Θ(n)
 */
char* csb_build(CStrBuilder *const builder)
{
    io_assert(builder != NULL, IO_MSG_NULL_PTR);

    /* String is size + 1 because of the NULL character. */
    char* const string = malloc(sizeof(char) * vect_size(builder->vect) + 1);

    unsigned int index = 0;
    vect_Iterator* const iter = vect_iter(builder->vect, 0);
    while (vect_iter_has_next(iter))
    {
        /* Grab the letter inside the underlying Vector and place it into the String. */
        char* const letter = vect_iter_next(iter);
        string[index++] = *letter;
        mem_free(letter, sizeof(char));
    }

    vect_iter_destroy(iter);
    vect_destroy(builder->vect);
    mem_free(builder, sizeof(CStrBuilder));

    /* Terminate the String before handing it to the user. */
    string[index] = CSB_NULL_CHAR;
    return string;
}
