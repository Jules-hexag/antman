/*
** EPITECH PROJECT, 2023
** antman
** File description:
** file
*/

#ifndef FILE_H_
    #define FILE_H_

    #include <stddef.h>
    #include <stdint.h>

    #include "bytes.h"

    #define FILE_CHUNK_SIZE 32768

    /**
     * @brief Opened file.
     */
    typedef struct {
        int fd;
        bytes_t *bytes;
    } file_t;

    /**
     * @brief Open the file in read-only mode.
     *
     * @param path Path of the file.
     * @return file_t* Opened file.
     */
    file_t *open_file(char *path);

    /**
     * @brief Read x bytes from the file. Data can be obtained from
     * `file.buffer`. Number of bytes read is stored in `file.read_size`.
     *
     * @param file File to read from.
     * @param size Number of bytes to read.
     * @return int 0 on success, -1 on error
     */
    int file_read_bytes(file_t *file, size_t size);

    /**
     * @brief Read a 32Kb chunk from the file. Data can be obtained from
     * `file.buffer`. Number of bytes read is stored in `file.read_size`.
     *
     * @param file File to read from.
     * @return int 0 on success, -1 on error
     */
    int file_read_chunk(file_t *file);

    /**
     * @brief Close and free a file.
     *
     * @param file The file to close.
     */
    void close_file(file_t *file);

#endif /* !FILE_H_ */
