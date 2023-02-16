/*
** EPITECH PROJECT, 2023
** antman
** File description:
** parse
*/

#ifndef PARSE_H_
    #define PARSE_H_

    /**
     * @brief Parse an unsigned int from a string.
     *
     * @param str String to parse the number from.
     * @param number Reference to the parsed number.
     * @return int -1 on error, 0 otherwise.
     */
    int parse_uint(char *str, unsigned int *number);

    int my_strncmp(char const *s1, char const *s2, int n);

#endif /* !PARSE_H_ */
