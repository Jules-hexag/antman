/*
** EPITECH PROJECT, 2023
** antman
** File description:
** bytes
*/

#ifndef BYTES_H_
    #define BYTES_H_

    #include <stddef.h>
    #include <stdint.h>

    /**
     * @brief Dynamically allocated byte array.
     */
    typedef struct {
        uint8_t *data;
        size_t size;
        size_t capacity;
    } bytes_t;

    /* Init functions */

    /**
     * @brief Create a new byte array.
     *
     * @param capacity Initial capacity of the array.
     * @return bytes_t* Byte array (NULL on error).
     */
    bytes_t *bytes_new(size_t capacity);

    /**
     * @brief Reserve capacity for a byte array.
     *
     * @param bytes Byte array.
     * @param capacity Capacity to reserve.
     * @return int 0 on success, -1 on error.
     */
    int bytes_reserve(bytes_t *bytes, size_t capacity);

    /* Access functions */

    /**
     * @brief Push bytes to a byte array.
     *
     * @param bytes Byte array.
     * @param data Data to push.
     * @param size Size of the data.
     * @return int 0 on success, -1 on error.
     */
    int bytes_push(bytes_t *bytes, const uint8_t *data, size_t size);

    /**
     * @brief Read multiple bytes as a single unsigned integer. This does not
     * check for size or advance the view, this must be done separately.
     *
     * @param data Raw byte array (size not checked).
     * @param size Number of bytes to read.
     * @return uint64_t Bytes as an unsigned integer.
     */
    uint64_t read_bytes(const uint8_t *data, size_t size);

    /* Destroy functions */

    /**
     * @brief Free a byte array.
     *
     * @param bytes Byte array.
     */
    void bytes_free(bytes_t *bytes);

#endif /* !BYTES_H_ */
