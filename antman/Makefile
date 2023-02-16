##
## EPITECH PROJECT, 2022
## antman
## File description:
## Makefile
##

SRC				:=	src/main.c \
					src/compress.c \
					src/lzss.c \
					src/encoder/encode.c \
					src/encoder/chunk.c \

RELEASE_OUT		:=	antman
DEBUG_OUT		:=	antman_debug

BUILD_DIR		:= 	../build/antman
RELEASE_DIR 	:= 	../build/antman/release
DEBUG_DIR		:= 	../build/antman/debug

LIB_DIR			:=	../lib
LIB_RELEASE		:=	$(LIB_DIR)/libantman.a
LIB_DEBUG		:=	$(LIB_DIR)/libantman_debug.a

CC				:=	gcc
CFLAGS			:=	-I./include/ -MMD -MP
LDFLAGS			:=	-L$(LIB_DIR)

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o))
RELEASE_FLAGS	:=	-O2 -flto
RELEASE_LIBS	:=	-lantman

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o))
DEBUG_FLAGS		:=	-g3 -Wall -Wextra -Wpedantic \
					-fsanitize=address -fsanitize=undefined
DEBUG_LIBS		:=	-lantman_debug

reset			:=  \033[0m
bold			:= 	\033[1m
underline 		:= 	\033[4m
green			:=  \033[32m
blue			:= 	\033[34m
magenta			:=	\033[35m
grey 			:= 	\033[90m

all: release

-include $(addprefix $(RELEASE_DIR)/,$(SRC:.c=.d))
-include $(addprefix $(DEBUG_DIR)/,$(SRC:.c=.d))

## BUILD ##

release: $(RELEASE_OUT)
	@printf "$(bold)$(green)antman compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)release$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(RELEASE_OUT)$(reset)\n"

debug: $(DEBUG_OUT)
	@printf "$(bold)$(green)antman compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)debug$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(DEBUG_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): LDFLAGS += $(RELEASE_LIBS)
$(RELEASE_OUT): $(RELEASE_OBJ) $(LIB_RELEASE)
	$(CC) -o $@ $(RELEASE_OBJ) $(CFLAGS) $(LDFLAGS)

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): LDFLAGS += $(DEBUG_LIBS)
$(DEBUG_OUT): $(DEBUG_OBJ) $(LIB_DEBUG)
	$(CC) -o $@ $(DEBUG_OBJ) $(CFLAGS) $(LDFLAGS)

$(LIB_RELEASE):
	@make release -C $(LIB_DIR) --no-print-directory

$(LIB_DEBUG):
	@make debug -C $(LIB_DIR) --no-print-directory

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
