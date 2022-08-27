/*

Vector C template

Author:
    Yoel Edery

Compile with:
    - gcc
    - clang

Tested compiler version:
    - gcc: 11.2.0 (Ubuntu 11.2.0-19ubuntu1)
    - clang: Ubuntu clang version 14.0.0-1ubuntu1

*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 128

#define MYERR(...)                                               \
    do {                                                         \
        printf("@ Vector Error: ./%s:%d: ", __FILE__, __LINE__); \
        printf(__VA_ARGS__);                                     \
    } while (0)

/* CREATE_VECTOR MACRO: Example CREATE_VECTOR(name, type) */
#define CREATE_VECTOR(name, type)      \
    typedef struct vector_##name##_s { \
        size_t size;                   \
        size_t capacity;               \
        type *array;                   \
    } vector_##name##_t;

/* VECTOR_INIT_SIZE MACRO: Initialize a vector with a given size */
#define VECTOR_INIT_SIZE(vector, name_var, size)                     \
    vector_##vector##_t *name_var = (vector_##vector##_t *)calloc(1, \
    sizeof(vector_##vector##_t));                                    \
    VECTOR_RESERVE(name_var, size);                                  \
    if (!name_var) {                                                 \
        MYERR("calloc failed\n");                                    \
        exit(84);                                                    \
    }

#define VECTOR_INIT_DEFAULT(vector, name_var) \
    VECTOR_INIT_SIZE(vector, name_var, BUFFER)

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4

#define VECTOR_INIT_CHOOSER(...) \
    GET_4TH_ARG(__VA_ARGS__, VECTOR_INIT_SIZE, VECTOR_INIT_DEFAULT, )

/* VECTOR_INIT MACRO: Initialize a vector with default */
/* buffer size or you can tell the size */
#define VECTOR_INIT(...) VECTOR_INIT_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/* VECTOR_RESERVE: Reserve a given size for a vector */
#define VECTOR_RESERVE(vector, CAPACITY)                              \
    do {                                                              \
        vector->array = (typeof(vector->array))realloc(vector->array, \
        (vector->capacity + CAPACITY) *                               \
        sizeof(typeof(vector->array[0])));                            \
        if (!vector->array) {                                         \
            MYERR("realloc failed\n");                                \
            exit(84);                                                 \
        }                                                             \
        vector->capacity += CAPACITY;                                 \
    } while (0)

#define NUMARGS(type, ...) \
    (sizeof((typeof(type)[]){type, ##__VA_ARGS__}) / sizeof(typeof(type)) - 1)

/* VECTOR_PUSH_BACK: Push a value at the end of a vector */
#define VECTOR_PUSH_BACK(vector, ...)                             \
    do {                                                          \
        if (!vector) {                                            \
            MYERR("vector is NULL\n");                            \
            break;                                                \
        }                                                         \
        size_t num_args = NUMARGS(vector->array[0], __VA_ARGS__); \
        if (vector->size >= vector->capacity                      \
        || vector->size + num_args >= vector->capacity) {         \
            VECTOR_RESERVE(vector, BUFFER);                       \
        }                                                         \
        for (size_t i = 0; i < num_args / BUFFER; i++) {          \
            VECTOR_RESERVE(vector, BUFFER);                       \
        }                                                         \
        typeof(vector->array[0]) args[] = {__VA_ARGS__};          \
        for (size_t i = 0; i < num_args; i++) {                   \
            vector->array[vector->size] = args[i];                \
            vector->size += 1;                                    \
        }                                                         \
    } while (0)

/* VECTOR_PUSH_AT: Push a value at a given index */
#define VECTOR_PUSH_AT(vector, index, ...)                               \
    do {                                                                 \
        if (!vector) {                                                   \
            MYERR("vector is NULL\n");                                   \
            break;                                                       \
        }                                                                \
        if (((long)index > (long)vector->size) || (long)index < 0) {     \
            MYERR("index out of range\n");                               \
            exit(84);                                                    \
        }                                                                \
        if ((long)index == (long)vector->size) {                         \
            VECTOR_PUSH_BACK(vector, __VA_ARGS__);                       \
            break;                                                       \
        }                                                                \
        size_t num_args = NUMARGS(vector->array[0], __VA_ARGS__);        \
        if (vector->size >= vector->capacity                             \
        || vector->size + num_args >= vector->capacity) {                \
            VECTOR_RESERVE(vector, BUFFER);                              \
        }                                                                \
        typeof(vector->array[0]) args[] = {__VA_ARGS__};                 \
        for (size_t i = 0; i < num_args / BUFFER; i++) {                 \
            VECTOR_RESERVE(vector, BUFFER);                              \
        }                                                                \
        memmove(&vector->array[index + num_args],                        \
        &vector->array[index],                                           \
        (vector->size - index) * sizeof(vector->array[0]));              \
        for (size_t i = 0; i < num_args; i++) {                          \
            vector->array[index + i] = args[i];                          \
            vector->size += 1;                                           \
        }                                                                \
    } while (0)

/* VECTOR_PUSH_FRONT: Push a value at the front of a vector */
#define VECTOR_PUSH_FRONT(vector, ...) \
    VECTOR_PUSH_AT(vector, 0, __VA_ARGS__)

/* VECTOR_POP_BACK: Pop a value at the end of a vector */
#define VECTOR_POP_BACK(vector)         \
    do {                                \
        if (!vector) {                  \
            MYERR("vector is NULL\n");  \
            break;                      \
        }                               \
        if (vector->size == 0) {        \
            MYERR("vector is empty\n"); \
            exit(84);                   \
        }                               \
        --vector->size;                 \
    } while (0)

/* VECTOR_POP_FRONT: Pop a value at the front of a vector */
#define VECTOR_POP_FRONT(vector)             \
    do {                                     \
        if (!vector) {                       \
            MYERR("vector is NULL\n");       \
            break;                           \
        }                                    \
        if (vector->size == 0) {             \
            MYERR("vector is empty\n");      \
            exit(84);                        \
        }                                    \
        PRIVATE_VECTOR_REMOVE_AT(vector, 0); \
    } while (0)

/* VECTOR_AT: Get a value at a given index */
#define VECTOR_AT(vector, index) vector->array[index]

/* VECTOR_SIZE: Get the size of a vector */
#define VECTOR_SIZE(vector) vector->size

/* VECTOR_FIRST: Get the first value of a vector */
#define VECTOR_FIRST(vector) VECTOR_AT(vector, 0)

/* VECTOR_LAST: Get the last value of a vector */
#define VECTOR_LAST(vector) VECTOR_AT(vector, vector->size)

/* VECTOR_CAPACITY: Get the capacity of a vector */
#define VECTOR_CAPACITY(vector) vector->capacity

/* PRIVATE_VECTOR_REMOVE_AT: Remove a value at a given index */
#define PRIVATE_VECTOR_REMOVE_AT(vector, index)                   \
    do {                                                          \
        if (!vector) {                                            \
            MYERR("vector is NULL\n");                            \
            break;                                                \
        }                                                         \
        memmove(vector->array + index, vector->array + index + 1, \
        (vector->size - index - 1) * sizeof(vector->array[0]));   \
        --vector->size;                                           \
    } while (0)

/* VECTOR_POP_AT: Pop a value at a given index */
#define VECTOR_POP_AT(vector, index)             \
    do {                                         \
        if (!vector) {                           \
            MYERR("vector is NULL\n");           \
            break;                               \
        }                                        \
        if (index >= vector->size) {             \
            MYERR("index out of range\n");       \
            exit(84);                            \
        }                                        \
        PRIVATE_VECTOR_REMOVE_AT(vector, index); \
    } while (0)

/* VECTOR_DELETE_ARRAY: Delete a vector array */
#define VECTOR_DELETE_ARRAY(vector)          \
    do {                                     \
        if (!vector->array) {                \
            MYERR("vector array is NULL\n"); \
            break;                           \
        }                                    \
        free(vector->array);                 \
        vector->array = NULL;                \
    } while (0)

/* DELETE_VECTOR: Delete a vector */
#define VECTOR_DELETE(vector)          \
    do {                               \
        if (!vector) {                 \
            MYERR("vector is NULL\n"); \
            break;                     \
        }                              \
        VECTOR_DELETE_ARRAY(vector);   \
        free(vector);                  \
        vector = NULL;                 \
    } while (0)

/* VECTOR_BEGIN: Get the begin iterator of a vector */
#define VECTOR_BEGIN(vector) vector->array

/* VECTOR_END: Get the end iterator of a vector */
#define VECTOR_END(vector) vector->array + vector->size

/* VECTOR_CLEAR: Clear a vector (set size to 0) */
#define VECTOR_CLEAR(vector)           \
    do {                               \
        if (!vector) {                 \
            MYERR("vector is NULL\n"); \
            break;                     \
        }                              \
        vector->size = 0;              \
    } while (0)

/* VECTOR_FOREACH: Iterate over a vector */
#define VECTOR_FOREACH(vector, it) \
    for (size_t it = 0; it < VECTOR_SIZE(vector); ++it)

/* VECTOR_FOREACH_AUTO: Iterate over a vector and give pointer to type */
#define VECTOR_FOREACH_AUTO(vector, it)                          \
    for (typeof(VECTOR_BEGIN(vector)) it = VECTOR_BEGIN(vector); \
         it != VECTOR_END(vector); ++it)

/* VECTOR_FOREACH_AUTO_BACK: Iterate over a vector in reverse order */
/* and give pointer to type */
#define VECTOR_FOREACH_AUTO_BACK(vector, it)                     \
    for (typeof(VECTOR_END(vector)) it = VECTOR_END(vector) - 1; \
         it != VECTOR_BEGIN(vector); --it)

/* VECTOR_FOREACH_BACKWARD: Iterate over a vector in reverse order */
#define VECTOR_FOREACH_BACKWARD(vector, it) \
    for (long it = VECTOR_SIZE(vector) - 1; it >= 0; --it)

/* VECTOR_SWAP: Swap two values at two given indices */
#define VECTOR_SWAP(vector, index1, index2)                     \
    do {                                                        \
        if (!vector) {                                          \
            MYERR("vector is NULL\n");                          \
            break;                                              \
        }                                                       \
        if (index1 >= vector->size || index2 >= vector->size) { \
            MYERR("index out of range\n");                      \
            exit(84);                                           \
        }                                                       \
        typeof(vector->array[0]) tmp = vector->array[index1];   \
        vector->array[index1] = vector->array[index2];          \
        vector->array[index2] = tmp;                            \
    } while (0)

/* VECTOR_MERGE: Merge two vectors */
#define VECTOR_MERGE(vector1, vector2)                              \
    do {                                                            \
        if (!vector1 || !vector2) {                                 \
            MYERR("vector is NULL\n");                              \
            break;                                                  \
        }                                                           \
        if (vector1->capacity < vector1->size + vector2->size) {    \
            VECTOR_RESERVE(vector1, vector1->size + vector2->size); \
        }                                                           \
        memcpy(vector1->array + vector1->size, vector2->array,      \
        vector2->size * sizeof(vector2->array[0]));                 \
        vector1->size += vector2->size;                             \
    } while (0)

/* VECTOR_ERASE_IF: Erase a value if a condition is true */
#define VECTOR_ERASE_IF(vector, index, condition) \
    do {                                          \
        if (!vector) {                            \
            MYERR("vector is NULL\n");            \
            break;                                \
        }                                         \
        if (condition) {                          \
            VECTOR_POP_AT(vector, index);         \
        }                                         \
    } while (0)

/* VECTOR_ERASE_ALL_IF: Erase all values if a condition is true */
#define VECTOR_ERASE_ALL_IF(vector, value, condition, compare) \
    do {                                                       \
        if (!vector) {                                         \
            MYERR("vector is NULL\n");                         \
            break;                                             \
        }                                                      \
        VECTOR_FOREACH(vector, it)                             \
        if (condition) {                                       \
            if (compare(vector->array[it], value)) {           \
                VECTOR_POP_AT(vector, it);                     \
                --it;                                          \
            }                                                  \
        }                                                      \
    } while (0)

/* VECTOR_SORT: Sort values in a vector */
#define VECTOR_SORT(vector, compare)                               \
    do {                                                           \
        if (!vector) {                                             \
            MYERR("vector is NULL\n");                             \
            break;                                                 \
        }                                                          \
        for (size_t i = 0; i < vector->size; ++i) {                \
            for (size_t j = i + 1; j < vector->size; ++j) {        \
                if (compare(vector->array[i], vector->array[j])) { \
                    VECTOR_SWAP(vector, i, j);                     \
                }                                                  \
            }                                                      \
        }                                                          \
    } while (0)

#endif /* !VECTOR_H_ */
