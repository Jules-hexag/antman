/*
** EPITECH PROJECT, 2023
** antman
** File description:
** write
*/

#include <stddef.h>
#include <stdint.h>

#include "bytes.h"
#include "macros.h"
#include "chunk.h"

size_t write_chunk_header(chunk_header_t *header, bytes_t *bytes)
{
    uint8_t data[] = {
        header->size >> 8,
        header->size,
    };

    if (bytes_push(bytes, data, CHUNK_HEADER_SIZE) == ERROR_RETURN) {
        return (0);
    } else {
        return (CHUNK_HEADER_SIZE);
    };
}

size_t write_raw_chunk(raw_chunk_t *chunk, bytes_t *bytes)
{
    uint16_t size_offset = chunk->size - 1;

    uint8_t data[] = {
        CHUNK_RAW << 6 | (size_offset >> 8 & 0x3F),
        size_offset,
    };

    if (bytes_push(bytes, data, CHUNK_RAW_SIZE) == ERROR_RETURN) {
        return (0);
    }

    if (bytes_push(bytes, chunk->data, chunk->size) == ERROR_RETURN) {
        return (0);
    }

    return (CHUNK_RAW_SIZE + chunk->size);
}

size_t write_dict_chunk(dict_chunk_t *chunk, bytes_t *bytes)
{
    uint8_t data[] = {
        CHUNK_DICT << 6 | (chunk->index >> 8 & 0x3F),
    };

    if (bytes_push(bytes, data, CHUNK_DICT_SIZE) == ERROR_RETURN) {
        return (0);
    } else {
        return (CHUNK_DICT_SIZE);
    }
}
