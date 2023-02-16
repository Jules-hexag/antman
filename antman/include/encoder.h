/*
** EPITECH PROJECT, 2023
** antman
** File description:
** encoder
*/

#ifndef ENCODER_H_
    #define ENCODER_H_

    #include "lib/bytes.h"
    #include "lib/chunk.h"

    #define RAW_MAX_SIZE 16384

    /**
     * @brief Encoder struct that keep track of the current encoding state of
     * a chunk.
     */
    typedef struct {
        bytes_t *buffer;
        bytes_t *pending_raw;
    } encoder_t;

    /**
     * @brief Creates a new encoder.
     */
    encoder_t *encoder_new(void);

    /**
     * @brief Push an unencoded byte to the encoder.
     *
     * @param encoder Encoder.
     * @param byte Byte to encode.
     * @return int 0 on success, -1 on error.
     */
    int encode_byte(encoder_t *encoder, uint8_t byte);

    /**
     * @brief Write the pending bytes into the output buffer.
     *
     * @param encoder Encoder.
     * @return int 0 on success, -1 on error.
     */
    int encoder_write_raw(encoder_t *encoder);


    /**
     * @brief Push an LZSS chunk to the encoder.
     *
     * @param encoder Encoder.
     * @param chunk Chunk to encode.
     * @return int 0 on success, -1 on error.
     */
    int encode_lzss_chunk(encoder_t *encoder, lzss_chunk_t chunk);

    /**
     * @brief Put the encoded bytes into the output buffer with the header.
     *
     * @param encoder Encoder.
     * @param output Output buffer.
     * @return int 0 on success, -1 on error.
     */
    int encoder_output(encoder_t *encoder, bytes_t *output);

    /**
     * @brief Free an encoder.
     */
    void free_encoder(encoder_t *encoder);

#endif /* !ENCODER_H_ */
