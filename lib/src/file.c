/*
** EPITECH PROJECT, 2023
** antman
** File description:
** file
*/

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bytes.h"
#include "macros.h"
#include "file.h"

file_t *open_file(char *path)
{
    file_t *file = malloc(sizeof(file_t));
    bytes_t *bytes = bytes_new(FILE_CHUNK_SIZE);
    if (file == NULL || bytes == NULL) return NULL;

    struct stat file_stats;
    stat(path, &file_stats);
    if ((file_stats.st_mode & S_IREAD) != S_IREAD) return NULL;

    int fd = open(path, O_RDONLY);
    if (fd == -1) return NULL;
    *file = (file_t) {fd, bytes};
    return file;
}

int file_read_bytes(file_t *file, size_t size)
{
    CATCH_ERR(bytes_reserve(file->bytes, size));

    int bytes_read = read(file->fd, file->bytes->data, size);
    if (bytes_read == -1) return ERROR_RETURN;

    file->bytes->size = bytes_read;

    return SUCCESS_RETURN;
}

int file_read_chunk(file_t *file)
{
    return file_read_bytes(file, FILE_CHUNK_SIZE);
}

void close_file(file_t *file)
{
    close(file->fd);
    bytes_free(file->bytes);
    free(file);
}
