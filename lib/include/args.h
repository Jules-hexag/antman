/*
** EPITECH PROJECT, 2023
** antman
** File description:
** args
*/

#ifndef ARGS_H_
    #define ARGS_H_

    /**
     * @brief Mode used to compress the file (depending on the file type).
     */
    typedef enum {
        LYRICS = 1,
        HTML = 2,
        PPM = 3,
    } mode_t;

    /**
     * @brief Arguments passed to the program.
     */
    typedef struct {
        mode_t mode;
        char *input_path;
    } args_t;

    /**
     * @brief Parse the arguments passed to the program.
     */
    int parse_args(int argc, char **argv, args_t *args);

#endif /* !ARGS_H_ */
