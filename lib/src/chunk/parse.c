/*
** EPITECH PROJECT, 2023
** antman
** File description:
** parse
*/

#include <stdint.h>

#include "bytes.h"
#include "chunk.h"

size_t parse_chunk_header(const bytes_t *bytes, size_t index,
    chunk_header_t *header)
{
    if (bytes->size - index < CHUNK_HEADER_SIZE)
        return (0);

    *header = (chunk_header_t) {read_bytes(&bytes->data[index], 2)};

    return (CHUNK_HEADER_SIZE);
}

chunk_type_t get_chunk_type(const bytes_t *bytes, size_t index)
{
    if (bytes->size - index < 1) return (CHUNK_UNKNOWN);

    uint8_t type = (bytes->data[index] & 0xC0) >> 6;

    if (type == 0x0) return (CHUNK_RAW);
    if (type == 0x1) return (CHUNK_LZSS_SMALL);
    if (type == 0x2) return (CHUNK_LZSS_LARGE);
    if (type == 0x3) return (CHUNK_DICT);

    return (CHUNK_UNKNOWN);
}

size_t parse_raw_chunk(const bytes_t *bytes, size_t index, raw_chunk_t *chunk)
{
    if (bytes->size - index < CHUNK_RAW_SIZE) return (0);

    uint16_t size_raw = read_bytes(&bytes->data[index], 2) & 0x3FFF;
    uint16_t size = size_raw + 1;

    if (bytes->size - index < (uint16_t) (CHUNK_RAW_SIZE + size)) return (0);
    uint8_t *data = &bytes->data[index + CHUNK_RAW_SIZE];

    *chunk = (raw_chunk_t) {size, data};

    return (CHUNK_RAW_SIZE + chunk->size);
}

size_t parse_dict_chunk(const bytes_t *bytes, size_t index, dict_chunk_t *chunk)
{
    if (bytes->size - index < CHUNK_DICT_SIZE) return (0);

    uint8_t dict_index = bytes->data[index] & 0x3F;

    *chunk = (dict_chunk_t) {dict_index};

    return (CHUNK_DICT_SIZE);
}
