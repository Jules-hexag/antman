/*
** EPITECH PROJECT, 2023
** antman
** File description:
** alloc
*/

#include <malloc.h>

#include "encoder.h"

#include "lib/bytes.h"
#include "lib/macros.h"
#include "lib/file.h"

encoder_t *encoder_new(void)
{
    encoder_t *encoder = malloc(sizeof(encoder_t));
    if (encoder == NULL) return NULL;

    encoder->buffer = bytes_new(FILE_CHUNK_SIZE);
    encoder->pending_raw = bytes_new(64);
    if (encoder->buffer == NULL || encoder->pending_raw == NULL) return NULL;

    return encoder;
}

int encoder_output(encoder_t *encoder, bytes_t *output)
{
    CATCH_ERR(encoder_write_raw(encoder));

    chunk_header_t header = {
        .size = encoder->buffer->size,
    };

    if (write_chunk_header(&header, output) == 0) return ERROR_RETURN;
    CATCH_ERR(bytes_push(output, encoder->buffer->data, encoder->buffer->size));

    encoder->buffer->size = 0;

    return SUCCESS_RETURN;
}

void free_encoder(encoder_t *encoder)
{
    bytes_free(encoder->buffer);
    bytes_free(encoder->pending_raw);
    free(encoder);
}
