/*
** EPITECH PROJECT, 2023
** antman
** File description:
** chunk
*/

#include "encoder.h"

#include "lib/bytes.h"
#include "lib/macros.h"

int encode_byte(encoder_t *encoder, uint8_t byte)
{
    if (encoder->pending_raw->size >= RAW_MAX_SIZE)
        CATCH_ERR(encoder_write_raw(encoder));

    return bytes_push(encoder->pending_raw, &byte, 1);
}

int encoder_write_raw(encoder_t *encoder)
{
    if (encoder->pending_raw->size == 0) return SUCCESS_RETURN;

    raw_chunk_t raw_chunk = {
        .size = encoder->pending_raw->size,
        .data = encoder->pending_raw->data
    };

    if (write_raw_chunk(&raw_chunk, encoder->buffer) == 0)
        return ERROR_RETURN;

    encoder->pending_raw->size = 0;

    return SUCCESS_RETURN;
}

int encode_lzss_chunk(encoder_t *encoder, lzss_chunk_t chunk)
{
    CATCH_ERR(encoder_write_raw(encoder));

    if (write_lzss_chunk(&chunk, encoder->buffer) == 0)
        return ERROR_RETURN;

    return SUCCESS_RETURN;
}
