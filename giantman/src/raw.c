/*
** EPITECH PROJECT, 2023
** antman
** File description:
** raw
*/

#include "lib/macros.h"
#include "lib/chunk.h"
#include "lib/bytes.h"

int raw_decompress(bytes_t *bytes, size_t *index, bytes_t *output)
{
    raw_chunk_t chunk;
    size_t read_bytes = parse_raw_chunk(bytes, *index, &chunk);
    if (read_bytes == 0) return ERROR_RETURN;

    CATCH_ERR(bytes_push(output, chunk.data, chunk.size));
    *index += read_bytes;

    return SUCCESS_RETURN;
}
