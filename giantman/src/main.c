/*
** EPITECH PROJECT, 2023
** antman
** File description:
** main
*/

#include <unistd.h>

#include "decompress.h"

#include "lib/args.h"
#include "lib/macros.h"

int main(int argc, char **argv)
{
    args_t args;
    int parse_return = 0;
    if ((parse_return = parse_args(argc, argv, &args)) == ERROR_RETURN) {
        write(STDERR, "Usage: ./giantman [input_path] [mode]\n", 38);
        return (ERROR_EXIT);
    } else if (parse_return == 1) return SUCCESS_RETURN;

    if (giantman_decompress(args) == ERROR_RETURN) {
        write(STDERR, "Error: error while decompressing file.\n", 39);
        return (ERROR_EXIT);
    }

    return (SUCCESS_EXIT);
}
