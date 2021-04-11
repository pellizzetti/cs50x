#include "utils.h"

#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Disable warnings from some compilers about the way we use variadic arguments
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

/**
 * Number of strings allocated by get_string.
 */
static size_t allocations = 0;

/**
 * Array of strings allocated by get_string.
 */
static string* strings = NULL;

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
#undef get_string
string get_string(va_list* args, const char* format, ...) {
    // Check whether we have room for another string
    if (allocations == SIZE_MAX / sizeof(string)) {
        return NULL;
    }

    // Growable buffer for characters
    string buffer = NULL;

    // Capacity of buffer
    size_t capacity = 0;

    // Number of characters actually in buffer
    size_t size = 0;

    // Character read or EOF
    int c;

    // Prompt user
    if (format != NULL) {
        // Initialize variadic argument list
        va_list ap;

        // Students' code will pass in printf-like arguments as variadic
        // parameters. The student-facing get_string macro always sets args to
        // NULL. In this case, we initialize the list of variadic parameters
        // the standard way with va_start.
        if (args == NULL) {
            va_start(ap, format);
        }

        // When functions in this library call get_string they will have
        // already stored their variadic parameters in a `va_list` and so they
        // just pass that in by pointer.
        else {
            // Put a copy of argument list in ap so it is not consumed by vprintf
            va_copy(ap, *args);
        }

        // Print prompt
        vprintf(format, ap);

        // Clean up argument list
        va_end(ap);
    }

    // Iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and
    // CRLF (Windows)
    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF) {
        // Grow buffer if necessary
        if (size + 1 > capacity) {
            // Increment buffer's capacity if possible
            if (capacity < SIZE_MAX) {
                capacity++;
            } else {
                free(buffer);
                return NULL;
            }

            // Extend buffer's capacity
            string temp = realloc(buffer, capacity);
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // Append current character to buffer
        buffer[size++] = c;
    }

    // Check whether user provided no input
    if (size == 0 && c == EOF) {
        return NULL;
    }

    // Check whether user provided too much input (leaving no room for trailing NUL)
    if (size == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    // If last character read was CR, try to read LF as well
    if (c == '\r' && (c = fgetc(stdin)) != '\n') {
        // Return NULL if character can't be pushed back onto standard input
        if (c != EOF && ungetc(c, stdin) == EOF) {
            free(buffer);
            return NULL;
        }
    }

    // Minimize buffer
    string s = realloc(buffer, size + 1);
    if (s == NULL) {
        free(buffer);
        return NULL;
    }

    // Terminate string
    s[size] = '\0';

    // Resize array so as to append string
    string* tmp = realloc(strings, sizeof(string) * (allocations + 1));
    if (tmp == NULL) {
        free(s);
        return NULL;
    }
    strings = tmp;

    // Append string to array
    strings[allocations] = s;
    allocations++;

    // Return string
    return s;
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
int get_int(const char* format, ...) {
    va_list ap;
    va_start(ap, format);

    // Try to get an int from user
    while (true) {
        // Get line of text, returning INT_MAX on failure
        string line = get_string(&ap, format);
        if (line == NULL) {
            va_end(ap);
            return INT_MAX;
        }

        // Return an int if only an int (in range) was provided
        if (strlen(line) > 0 && !isspace((unsigned char)line[0])) {
            char* tail;
            errno = 0;
            long n = strtol(line, &tail, 10);
            if (errno == 0 && *tail == '\0' && n >= INT_MIN && n < INT_MAX) {
                va_end(ap);
                return n;
            }
        }
    }
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long; if text does not represent a long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LONG_MAX.
 */
long get_long(const char* format, ...) {
    va_list ap;
    va_start(ap, format);

    // Try to get a long from user
    while (true) {
        // Get line of text, returning LONG_MAX on failure
        string line = get_string(&ap, format);
        if (line == NULL) {
            va_end(ap);
            return LONG_MAX;
        }

        // Return a long if only a long (in range) was provided
        if (strlen(line) > 0 && !isspace((unsigned char)line[0])) {
            char* tail;
            errno = 0;
            long n = strtol(line, &tail, 10);
            if (errno == 0 && *tail == '\0' && n < LONG_MAX) {
                va_end(ap);
                return n;
            }
        }
    }
}

/**
 * Called automatically after execution exits main.
 */
static void teardown(void) {
    // Free library's strings
    if (strings != NULL) {
        for (size_t i = 0; i < allocations; i++) {
            free(strings[i]);
        }
        free(strings);
    }
}