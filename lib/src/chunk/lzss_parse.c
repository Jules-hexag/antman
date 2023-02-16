/*
** EPITECH PROJECT, 2023
** antman
** File description:
** lzss
*/

#include "bytes.h"
#include "chunk.h"

static size_t parse_lzss_small(const bytes_t *bytes, size_t index,
    lzss_chunk_t *chunk)
{
    if (bytes->size - index < CHUNK_LZSS_SMALL_SIZE) return (0);

    uint8_t offset_raw = bytes->data[index] & 0x3F;
    uint16_t offset = offset_raw + 1;
    uint16_t length = bytes->data[index + 1];

    *chunk = (lzss_chunk_t) {offset, length};

    return (CHUNK_LZSS_SMALL_SIZE);
}

static size_t parse_lzss_large(const bytes_t *bytes, size_t index,
    lzss_chunk_t *chunk)
{

    if (bytes->size - index < CHUNK_LZSS_LARGE_SIZE) return (0);

    uint16_t offset_raw = read_bytes(&bytes->data[index], 2) & 0x3FFF;
    uint16_t offset = offset_raw + 1;
    uint16_t length = read_bytes(&bytes->data[index + 2], 2);

    *chunk = (lzss_chunk_t) {offset, length};

    return (CHUNK_LZSS_LARGE_SIZE);
}

size_t parse_lzss_chunk(const bytes_t *bytes, size_t index,
    lzss_chunk_t *chunk, chunk_type_t type)
{
    if (type == CHUNK_LZSS_SMALL)
        return (parse_lzss_small(bytes, index, chunk));
    if (type == CHUNK_LZSS_LARGE)
        return (parse_lzss_large(bytes, index, chunk));

    return (0);
}
