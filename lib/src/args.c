/*
** EPITECH PROJECT, 2023
** antman
** File description:
** args
*/

#include "args.h"
#include "macros.h"
#include "parse.h"
#include <unistd.h>

int parse_args(int argc, char **argv, args_t *args)
{
    if (argc == 2 && !my_strncmp(argv[1], "-h", 2)) {
        write(STDOUT, "USAGE:\n\t./antman [PATH]\t--> will compress the given \
file.\n\t./giantman [PATH] --> will decompress the given file.\n", 113);
        return 1;
    }
    if (argc != 3)
        return (ERROR_RETURN);

    unsigned int mode;

    CATCH_ERR(parse_uint(argv[2], &mode));

    if (mode < 1 || mode > 3)
        return (ERROR_RETURN);

    args->mode = mode;
    args->input_path = argv[1];

    return (SUCCESS_RETURN);
}
