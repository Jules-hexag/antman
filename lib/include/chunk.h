/*
** EPITECH PROJECT, 2023
** antman
** File description:
** chunk
*/

#ifndef CHUNK_H_
    #define CHUNK_H_

    #include <stdint.h>
    #include <stddef.h>

    #include "bytes.h"

    #define CHUNK_HEADER_SIZE 2u
    #define CHUNK_RAW_SIZE 2u
    #define CHUNK_LZSS_SMALL_SIZE 2u
    #define CHUNK_LZSS_LARGE_SIZE 4u
    #define CHUNK_DICT_SIZE 1u

    #define LZSS_SMALL_MAX_OFFSET 64
    #define LZSS_SMALL_MAX_LENGTH 255

    /* Type definitions */

    /**
     * @brief Data chunk header.
     */
    typedef struct {
        uint16_t size;
    } chunk_header_t;

    typedef enum {
        CHUNK_RAW = 0x0u,
        CHUNK_LZSS_SMALL = 0x1u,
        CHUNK_LZSS_LARGE = 0x2u,
        CHUNK_DICT = 0x3u,
        CHUNK_UNKNOWN = 0xFFu,
    } chunk_type_t;

    /**
     * @brief Uncompressed chunk.
     */
    typedef struct {
        uint16_t size;
        uint8_t *data;
    } raw_chunk_t;

    /**
     * @brief LZSS chunk.
     */
    typedef struct {
        uint16_t offset;
        uint16_t length;
    } lzss_chunk_t;

    /**
     * @brief Dictionary chunk.
     */
    typedef struct {
        uint8_t index;
    } dict_chunk_t;

    /* Parsing functions */

    /**
     * @brief Parse a chunk header.
     *
     * @param bytes Bytes to parse.
     * @param header Header to fill.
     * @return Number of bytes read (0 on error).
     */
    size_t parse_chunk_header(const bytes_t *bytes, size_t index,
        chunk_header_t *header);

    /**
     * @brief Get the chunk type.
     *
     * @param bytes Bytes to parse.
     * @return Chunk type.
     */
    chunk_type_t get_chunk_type(const bytes_t *bytes, size_t index);

    /**
     * @brief Parse an uncompressed chunk.
     *
     * @param bytes Bytes to parse.
     * @param chunk Chunk to fill.
     * @return Number of bytes read (0 on error).
     */
    size_t parse_raw_chunk(const bytes_t *bytes, size_t index,
        raw_chunk_t *chunk);

    /**
     * @brief Parse a LZSS chunk.
     *
     * @param bytes Bytes to parse.
     * @param chunk Chunk to fill.
     * @return size_t Number of bytes read (0 on error).
     */
    size_t parse_lzss_chunk(const bytes_t *bytes, size_t index,
        lzss_chunk_t *chunk, chunk_type_t type);

    /**
     * @brief Parse a dictionary chunk.
     *
     * @param bytes Bytes to parse.
     * @param chunk Chunk to fill.
     * @return Number of bytes read (0 on error).
     */
    size_t parse_dict_chunk(const bytes_t *bytes, size_t index,
        dict_chunk_t *chunk);

    /* Writing functions */

    /**
     * @brief Write a chunk header.
     *
     * @param header Header to write.
     * @param bytes Bytes to write to.
     * @return Number of bytes written (0 on error).
     */
    size_t write_chunk_header(chunk_header_t *header, bytes_t *bytes);

    /**
     * @brief Write an uncompressed chunk.
     *
     * @param chunk Chunk to write.
     * @param bytes Bytes to write to.
     * @return Number of bytes written (0 on error).
     */
    size_t write_raw_chunk(raw_chunk_t *chunk, bytes_t *bytes);

    /**
     * @brief Write a LZSS chunk.
     *
     * @param chunk Chunk to write.
     * @param bytes Bytes to write to.
     * @return Number of bytes written (0 on error).
     */
    size_t write_lzss_chunk(lzss_chunk_t *chunk, bytes_t *bytes);

    /**
     * @brief Write a dictionary chunk.
     *
     * @param chunk Chunk to write.
     * @param bytes Bytes to write to.
     * @return Number of bytes written (0 on error).
     */
    size_t write_dict_chunk(dict_chunk_t *chunk, bytes_t *bytes);

#endif /* !CHUNK_H_ */
