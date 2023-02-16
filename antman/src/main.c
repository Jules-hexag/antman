/*
** EPITECH PROJECT, 2023
** antman
** File description:
** main
*/

#include <unistd.h>

#include "compress.h"

#include "lib/args.h"
#include "lib/macros.h"

int main(int argc, char **argv)
{
    args_t args;
    int parse_return = 0;
    if ((parse_return = parse_args(argc, argv, &args)) == ERROR_RETURN) {
        write(STDERR, "Usage: ./antman [input_path] [mode]\n", 36);
        return (ERROR_EXIT);
    } else if (parse_return == 1) return SUCCESS_RETURN;

    if (antman_compress(args) == ERROR_RETURN) {
        write(STDERR, "Error: error while compressing file.\n", 37);
        return (ERROR_EXIT);
    }

    return (SUCCESS_EXIT);
}
