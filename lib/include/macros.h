/*
** EPITECH PROJECT, 2023
** antman
** File description:
** constants
*/

#ifndef CONSTANTS_H_
    #define CONSTANTS_H_

    /* stdout/stderr file descriptions */
    #define STDOUT 1
    #define STDERR 2

    /* Exit codes */
    #define SUCCESS_EXIT 0
    #define ERROR_EXIT 84

    /* Function return codes */
    #define SUCCESS_RETURN 0
    #define ERROR_RETURN -1

    /* Compiler hints for branch prediction optimization */
    #if defined(__clang__) || (defined (__GNUC__) && (__GNUC__ > 2))
        #define LIKELY(c) __builtin_expect(!!(c), 1)
        #define UNLIKELY(c) __builtin_expect(!!(c), 0)
    #else
        #define LIKELY(c) (c)
        #define UNLIKELY(c) (c)
    #endif

    /* Helper macro to propagate errors */
    #define CATCH_ERR(expr) if ((expr) == ERROR_RETURN) return ERROR_RETURN

#endif /* !CONSTANTS_H_ */
