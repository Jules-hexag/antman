/*
** EPITECH PROJECT, 2023
** antman
** File description:
** create
*/

#include <stddef.h>
#include <stdint.h>
#include <malloc.h>

#include "macros.h"
#include "bytes.h"

bytes_t *bytes_new(size_t capacity)
{
    bytes_t *bytes = malloc(sizeof(bytes_t));
    if (bytes == NULL) return (NULL);

    uint8_t *data = malloc(sizeof(uint8_t) * capacity);
    if (data == NULL) {
        free(bytes);
        return (NULL);
    }

    *bytes = (bytes_t) {data, 0, capacity};

    return (bytes);
}

int bytes_reserve(bytes_t *bytes, size_t capacity)
{
    if (bytes->capacity >= capacity) return (SUCCESS_RETURN);

    uint8_t *new_data = malloc(sizeof(uint8_t) * capacity);
    if (new_data == NULL) return (ERROR_RETURN);

    for (size_t i = 0; i < bytes->size; i++) {
        new_data[i] = bytes->data[i];
    }

    free(bytes->data);
    bytes->data = new_data;
    bytes->capacity = capacity;

    return (SUCCESS_RETURN);
}

void bytes_free(bytes_t *bytes)
{
    free(bytes->data);
    free(bytes);
}
