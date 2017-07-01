
/*
 * File: CStrBuilder.h
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

#pragma once

#include "C-DataStructures/Vector.h"

/* Anonymous structures. */
typedef struct CStrBuilder CStrBuilder;

/* ~~~~~ Constructors ~~~~~ */

/*
 * Constructs a new CString Builder.
 *
 * NOTE: The Builder must be de-constructed after its usable life-span.
 */
CStrBuilder* CStrBuilder_new();

/* ~~~~~ Accessors ~~~~~ */

/* Returns the amount of characters in the String. */
size_t csb_size(const CStrBuilder* const builder);

/* ~~~~~ Mutators ~~~~~ */

/* Appends the specified String to the builder. */
void csb_append(CStrBuilder *const builder, const char *const str);
/* Appends the specified String to the builder. */
void csb_appendf(CStrBuilder *const builder, const char* format, ...);
/* Removes leading and trailing whitespace. */
void csb_trim(CStrBuilder *const builder);

/* ~~~~~ De-constructors ~~~~~ */

/* De-constructs the builder and returns its contents as a NULL terminated String. */
char* csb_build(CStrBuilder *const builder);
