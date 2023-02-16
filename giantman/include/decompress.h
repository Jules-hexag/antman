/*
** EPITECH PROJECT, 2023
** antman
** File description:
** decompress
*/

#ifndef DECOMPRESS_H_
    #define DECOMPRESS_H_

    #include <stddef.h>
    #include "lib/args.h"
    #include "lib/bytes.h"
    #include "lib/chunk.h"

    int giantman_decompress(args_t args);
    int giantman_decompress_chunk(bytes_t *bytes, bytes_t *output);

    /**
     * @brief pushes raw data in output
     *
     * @param bytes
     * @param index
     * @param output
     * @return ERROR_RETURN as an error
     */
    int raw_decompress(bytes_t *bytes, size_t *index, bytes_t *output);

    /**
     * @brief pushes decompressed lzss data in output
     *
     * @param bytes
     * @param index
     * @param output
     * @return ERROR_RETURN as an error
     */
    int lzss_decompress(bytes_t *bytes, size_t *index, bytes_t *output,
        chunk_type_t type);

    /**
     * @brief Get the chunk size from header
     *
     * @param bytes_t header
     * @return size_t size of the header, 0 if error
     */
    size_t get_chunk_header_size(bytes_t *bytes);

#endif /* !DECOMPRESS_H_ */
