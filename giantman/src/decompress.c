/*
** EPITECH PROJECT, 2023
** antman
** File description:
** decompress
*/

#include "lib/args.h"
#include "lib/macros.h"
#include "decompress.h"
#include "lib/chunk.h"
#include "lib/file.h"
#include <unistd.h>

int giantman_decompress(args_t args)
{
    bytes_t *output = bytes_new(FILE_CHUNK_SIZE);
    file_t *file = open_file(args.input_path);
    if (output == NULL || file == NULL) return ERROR_RETURN;

    while (1) {
        CATCH_ERR(file_read_bytes(file, 2));
        if (file->bytes->size == 0) break;
        size_t chunk_size = get_chunk_header_size(file->bytes);
        if (chunk_size == 0) return ERROR_RETURN;

        CATCH_ERR(file_read_bytes(file, chunk_size));
        if (file->bytes->size != chunk_size) return ERROR_RETURN;
        CATCH_ERR(giantman_decompress_chunk(file->bytes, output));
        write(STDOUT, output->data, output->size);
        output->size = 0;
    }

    close_file(file);
    bytes_free(output);
    return SUCCESS_RETURN;
}

int giantman_decompress_chunk(bytes_t *bytes, bytes_t *output)
{
    size_t index = 0;
    while (index < bytes->size) {
        chunk_type_t chunk_type = get_chunk_type(bytes, index);
        if (chunk_type == CHUNK_UNKNOWN) return ERROR_RETURN;
        if (chunk_type == CHUNK_RAW) raw_decompress(bytes, &index, output);
        if (chunk_type == CHUNK_LZSS_SMALL)
            lzss_decompress(bytes, &index, output, CHUNK_LZSS_SMALL);
        if (chunk_type == CHUNK_LZSS_LARGE)
            lzss_decompress(bytes, &index, output, CHUNK_LZSS_LARGE);
    }
    return SUCCESS_RETURN;
}

size_t get_chunk_header_size(bytes_t *bytes)
{
    chunk_header_t chunk_header;
    if (bytes->size != CHUNK_HEADER_SIZE) return 0;
    parse_chunk_header(bytes, 0, &chunk_header);
    return chunk_header.size;
}
