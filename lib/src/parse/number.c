/*
** EPITECH PROJECT, 2023
** antman
** File description:
** number
*/

#include <stddef.h>
#include <limits.h>

#include "macros.h"
#include "parse.h"

int parse_uint(char *str, unsigned int *number)
{
    unsigned int parsed = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (ERROR_RETURN);
        unsigned int unit = str[i] - '0';

        if (parsed > UINT_MAX / 10
            || (parsed == UINT_MAX / 10 && unit > UINT_MAX % 10))
            return (ERROR_RETURN);

        parsed = parsed * 10 + unit;
    }

    *number = parsed;
    return (SUCCESS_RETURN);
}
