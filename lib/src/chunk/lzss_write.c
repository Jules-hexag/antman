/*
** EPITECH PROJECT, 2023
** antman
** File description:
** lzss_write
*/

#include "chunk.h"
#include "macros.h"

static size_t write_lzss_large(lzss_chunk_t *chunk, bytes_t *bytes)
{
    uint16_t match_offset = chunk->offset - 1;

    uint8_t data[] = {
        CHUNK_LZSS_LARGE << 6 | (match_offset >> 8 & 0x3F),
        match_offset,
        chunk->length >> 8,
        chunk->length,
    };

    if (bytes_push(bytes, data, CHUNK_LZSS_LARGE_SIZE) == ERROR_RETURN) {
        return (0);
    } else {
        return (CHUNK_LZSS_LARGE_SIZE);
    }
}

static size_t write_lzss_small(lzss_chunk_t *chunk, bytes_t *bytes)
{
    uint8_t match_offset = chunk->offset - 1;

    uint8_t data[] = {
        CHUNK_LZSS_SMALL << 6 | (match_offset & 0x3F),
        chunk->length,
    };

    if (bytes_push(bytes, data, CHUNK_LZSS_SMALL_SIZE) == ERROR_RETURN) {
        return (0);
    } else {
        return (CHUNK_LZSS_SMALL_SIZE);
    }
}

size_t write_lzss_chunk(lzss_chunk_t *chunk, bytes_t *bytes)
{
    if (chunk->offset > LZSS_SMALL_MAX_OFFSET ||
        chunk->length > LZSS_SMALL_MAX_LENGTH) {
        return (write_lzss_large(chunk, bytes));
    } else {
        return (write_lzss_small(chunk, bytes));
    }
}
