##
## EPITECH PROJECT, 2022
## antman
## File description:
## Makefile
##

SRC				:=	src/args.c \
					src/file.c \
					src/bytes/alloc.c \
					src/bytes/access.c \
					src/chunk/parse.c \
					src/chunk/write.c \
					src/chunk/lzss_parse.c \
					src/chunk/lzss_write.c \
					src/parse/number.c \
					src/parse/my_strncmp.c

RELEASE_OUT		:=	libantman.a
DEBUG_OUT		:=	libantman_debug.a

BUILD_DIR		:= 	../build/lib
RELEASE_DIR 	:= 	../build/lib/release
DEBUG_DIR		:= 	../build/lib/debug

CC				:=	gcc
CFLAGS			:=	-I./include/ -MMD -MP

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o))
RELEASE_FLAGS	:=	-O2 -flto

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o))
DEBUG_FLAGS		:=	-g3 -Wall -Wextra -Wpedantic \
					-fsanitize=address -fsanitize=undefined

reset			:=  \033[0m
bold			:= 	\033[1m
underline 		:= 	\033[4m
blue			:= 	\033[34m
magenta			:=	\033[35m
grey 			:= 	\033[90m

all: release

-include $(addprefix $(RELEASE_DIR)/,$(SRC:.c=.d))
-include $(addprefix $(DEBUG_DIR)/,$(SRC:.c=.d))

## BUILD ##

$(NAME): release

release: $(RELEASE_OUT)
	@printf "$(bold)$(magenta)libary compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)release$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(RELEASE_OUT)$(reset)\n"

debug: $(DEBUG_OUT)
	@printf "$(bold)$(magenta)libary compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)debug$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(DEBUG_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): $(RELEASE_OBJ)
	$(AR) rcs $@ $^

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): $(DEBUG_OBJ)
	$(AR) rcs $@ $^

## OBJECTS ##

$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

## CLEANING ##

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(RELEASE_OUT) $(DEBUG_OUT)

re: fclean all

.PHONY: all release debug clean fclean re
