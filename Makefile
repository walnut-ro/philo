NAME = philo

# Collors
RESET 	= \033[0m
GREEN 	= \033[0;32m
RED 	= \033[0;31m

OBJ_DIR	=	obj

# Compilation
CC = gcc -lpthread

# Compilation flags
# CFLAGS = -g -Wall -Werror -Wextra #Debug
CFLAGS = -Wall -Werror -Wextra #Normal Execution

RM		= rm -rf

SRCS 	= main.c validation.c utils.c init.c time.c \
			output.c garbage_collector.c mutex.c \
			routine_finish.c routine_dining.c

OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Build Successful$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@$(RM) obj
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo  "$(RED)Cleaning all...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)Cleaning binaries...$(RESET)"
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

.PHONY: all run re clean fclean