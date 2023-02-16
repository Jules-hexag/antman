/*
** EPITECH PROJECT, 2023
** antman
** File description:
** compress
*/

#include <unistd.h>

#include "compress.h"
#include "encoder.h"
#include "lzss.h"

#include "lib/args.h"
#include "lib/bytes.h"
#include "lib/macros.h"
#include "lib/file.h"

int antman_compress(args_t args)
{
    bytes_t *output = bytes_new(FILE_CHUNK_SIZE);
    file_t *file = open_file(args.input_path);
    if (output == NULL || file == NULL) return ERROR_RETURN;

    while (1) {
        CATCH_ERR(file_read_chunk(file));
        if (file->bytes->size == 0) break;
        CATCH_ERR(antman_compress_chunk(file->bytes, output));

        write(STDOUT, output->data, output->size);
        output->size = 0;
    }

    close_file(file);
    bytes_free(output);
    return SUCCESS_RETURN;
}

int antman_compress_chunk(bytes_t *bytes, bytes_t *output)
{
    encoder_t *encoder = encoder_new();
    if (encoder == NULL) return ERROR_RETURN;

    size_t search_start = 0;
    for (size_t i = 0; i < bytes->size; i++) {
        lzss_chunk_t match = search_match(bytes, search_start, i);
        if (match.length >= MIN_MATCH_LENGTH) {
            CATCH_ERR(encode_lzss_chunk(encoder, match));
            i += match.length - 1;
        } else {
            CATCH_ERR(encode_byte(encoder, bytes->data[i]));
        }

        if (i - search_start >= OFFSET_MAX) search_start = i - OFFSET_MAX + 1;
    }

    CATCH_ERR(encoder_output(encoder, output));
    free_encoder(encoder);
    return SUCCESS_RETURN;
}
