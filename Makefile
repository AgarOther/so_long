# Compilation
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT		= @make -C ./libft

LIB			= libft/libft.a
MLX			= MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

# Names
NAME		= so_long

# Sources & Includes
SRCS		=	srcs/main.c \
				srcs/parsing.c \
				srcs/parsing_utils.c \
				srcs/parsing_map.c \
				srcs/player_actions.c \
				srcs/textures.c \
				srcs/free.c

OBJ_FOLDER	= objs
INCLUDES	= includes

# Objects
OBJS		=	$(patsubst srcs/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

# Custom Makefile Flags
MAKEFLAGS	+= --no-print-directory

# Custom Colors
PURPLE		= \033[1;35m
LIGHT_GREEN	= \033[1;32m
RESET		= \033[0m

# Custom messages
EXE_DONE	= @echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN	= @echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN	= @echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all :
	@if [ -f $(NAME) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(NAME); \
	fi

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX) -o $(NAME)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir $(OBJ_FOLDER); \
	fi
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

libft : 
	@if [ ! -f $(LIB) ]; then \
        $(MAKE) -C ./libft; \
	fi

clean :
	@rm -f $(OBJS)
	@cd libft && make clean
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@rm -f $(NAME) $(OBJS)
	@cd libft && make fclean
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

f : $(NAME)

re : fclean all

.PHONY: all clean fclean re libft so_long f
