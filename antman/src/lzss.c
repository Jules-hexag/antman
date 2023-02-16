/*
** EPITECH PROJECT, 2023
** antman
** File description:
** lzss
*/

#include "lzss.h"

#include "lib/macros.h"

static size_t match_length(bytes_t *buffer, size_t position, size_t current)
{
    size_t length = 0;

    while (LIKELY(position < buffer->size) && LIKELY(current < buffer->size)
        && UNLIKELY(buffer->data[position] == buffer->data[current])) {
        position++;
        current++;
        length++;
    }

    return length;
}

lzss_chunk_t search_match(bytes_t *buffer, size_t search_start, size_t current)
{
    lzss_chunk_t match = {0, 0};
    size_t position = search_start;

    while (LIKELY(position < current)) {
        size_t new_length = match_length(buffer, position, current);
        if (new_length > match.length) {
            match.length = new_length;
            match.offset = current - position;
        }
        position++;
    }

    return match;
}
