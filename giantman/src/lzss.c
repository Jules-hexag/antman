/*
** EPITECH PROJECT, 2023
** antman
** File description:
** lzss
*/

#include "lib/bytes.h"
#include "lib/chunk.h"
#include "lib/macros.h"

int lzss_decompress(bytes_t *bytes, size_t *index, bytes_t *output,
    chunk_type_t type)
{
    lzss_chunk_t chunk;
    size_t bytes_read = parse_lzss_chunk(bytes, *index, &chunk, type);
    if (bytes_read == 0) return ERROR_RETURN;
    *index += bytes_read;

    if (chunk.offset > output->size) return ERROR_RETURN;
    size_t index_start = output->size - chunk.offset;

    CATCH_ERR(bytes_reserve(output, output->size + chunk.length));
    bytes_push(output, &output->data[index_start], chunk.length);

    return SUCCESS_RETURN;
}
