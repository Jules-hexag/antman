##
## EPITECH PROJECT, 2022
## antman
## File description:
## Makefile
##

BUILD_DIR		:= 	build
ANTMAN			:= 	antman
GIANTMAN 		:= 	giantman
LIB 			:= 	lib

all: release

## BUILD ##

release:
	@make release -C $(LIB) --no-print-directory
	@make release -C $(ANTMAN) --no-print-directory
	@make release -C $(GIANTMAN) --no-print-directory

debug:
	@make debug -C $(LIB) --no-print-directory
	@make debug -C $(ANTMAN) --no-print-directory
	@make debug -C $(GIANTMAN) --no-print-directory

## CLEANING ##

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	@make fclean -C $(ANTMAN) --no-print
	@make fclean -C $(GIANTMAN) --no-print
	@make fclean -C $(LIB) --no-print

re: fclean all

.PHONY: all release debug clean fclean re
