/*
** EPITECH PROJECT, 2023
** antman
** File description:
** lzss
*/

#ifndef LZSS_H_
    #define LZSS_H_

    #include "lib/bytes.h"
    #include "lib/chunk.h"

    #define OFFSET_MAX 16383
    #define LENGTH_MAX 65535
    #define MIN_MATCH_LENGTH 5

    /**
     * @brief Search through the search buffer for the longest match of
     * `current` in `search_start` using KMP algorithm.
     *
     * @param buffer Buffer to search in.
     * @param search_start Index of the search buffer.
     * @param current Index of current buffer.
     * @return lzss_chun_t Longest match found.
     */
    lzss_chunk_t search_match(bytes_t *buffer, size_t search_start,
        size_t current);

#endif /* !LZSS_H_ */
