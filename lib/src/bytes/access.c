/*
** EPITECH PROJECT, 2023
** antman
** File description:
** access
*/

#include <stdint.h>
#include <stddef.h>
#include <malloc.h>

#include "macros.h"
#include "bytes.h"

int bytes_push(bytes_t *bytes, const uint8_t *data, size_t size)
{
    CATCH_ERR(bytes_reserve(bytes, bytes->size + size));

    for (size_t i = 0; i < size; i++) {
        bytes->data[bytes->size + i] = data[i];
    }

    bytes->size += size;

    return (SUCCESS_RETURN);
}

uint64_t read_bytes(const uint8_t *data, size_t size)
{
    uint64_t value = 0;

    for (size_t i = 0; i < size; i++) {
        value |= data[i] << ((size - 1 - i) * 8);
    }

    return (value);
}
