#ifndef STRING_T_H
#define STRING_T_H

#include <stddef.h>
#include <string.h>

typedef struct string_t
{
    char * data;
    size_t length;
} string_t;

string_t * string_constructor(const char * input);
void string_free(string_t * str);

#ifndef STRING_T_IMPLEMENTATION_H
#define STRING_T_IMPLEMENTATION_H

#if defined(__unix__) || defined(__APPLE__)

#include <assert.h>
#include <stdlib.h>

#else

#error "Only unix-like systems"

#endif

string_t * string_constructor(const char * input) {
    assert(input != NULL);

    string_t *return_value = (string_t*)malloc(sizeof(string_t));
    if (return_value == NULL) {
        return NULL;
    }

    size_t _length = strlen(input);

    return_value->data = (char *)malloc(_length + 1);
    if (return_value->data == NULL) {
        free(return_value);
        return NULL;
    }

    strcpy(return_value->data, input);
    return_value->length = _length;

    return return_value;
}

void string_free(string_t * str) {
    assert(str != NULL);

    if(str->data != NULL) {
            free(str->data);
    }

    free(str);
}

#endif
#endif