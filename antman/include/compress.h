/*
** EPITECH PROJECT, 2023
** antman
** File description:
** compress
*/

#ifndef COMPRESS_H_
    #define COMPRESS_H_

    #include "lib/args.h"
    #include "lib/bytes.h"

    /**
     * @brief Compress a file with antman algorithm.
     */
    int antman_compress(args_t args);

    /**
     * @brief Compress a data chunk with antman algorithm. See `format.md` for
     * a description of the algorithm.
     */
    int antman_compress_chunk(bytes_t *bytes, bytes_t *output);

#endif /* !COMPRESS_H_ */
