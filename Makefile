NAME				=		philo

INC_DIR			=		./include
HEADER_FILE	=		$(INC_DIR)/philosophers.h
#LIBFT				=		libft
SRC_DIR			=		./src
SRCS				=		$(addprefix $(SRC_DIR)/, \
								main.c \
								create_table.c init_table.c \
								simulation.c \
								split_on.c strings.c \
								validate_argv.c validation_func.c )

OBJ_DIR			=		./obj
OBJS				=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#CFLAGS			=		-g -Wall -Wextra -Werror
#CFLAGS			=		-g -O0 -Werror
CFLAGS			=		-g -fsanitize=address #-Wall -Wextra -Werror
#LDFLAGS			=		-lreadline -lhistory
LDFLAGS			=		
CC					=		cc

all:	${NAME}

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) && \
		(printf "philo compiled successfully.\n")

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@printf "[philo] Object files cleaned.\n"

fclean: clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@printf "[philo] Cleaned successfully.\n"

re:	fclean all

.PHONY:	all clean fclean re
