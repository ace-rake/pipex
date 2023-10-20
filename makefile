NAME := pipex

HEADERS:= inc/pipex.h

ERRFLAGS:= -Wall -Werror -Wextra
FLAGS:= -g -O0
SRCS:= $(wildcard src/*.c)
MAIN:= main.c
TEST:= test.c

OBJDIR:= obj
MAIN_OBJ:= $(MAIN:%.c=$(OBJDIR)/%.o)
TEST_OBJ:= $(MAIN:%.c=$(OBJDIR)/%.o)
SRCS_OBJS:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

ALLFLAGS:= $(ERRFLAGS) $(FLAGS)

$(NAME): $(SRCS_OBJS) $(MAIN_OBJ) $(HEADERS)
	@echo "compiling $@"
	@make -C src/libft
	@cc $(ALLFLAGS) $(SRCS_OBJS) $(MAIN_OBJ) -Lsrc/libft -lft -o $@

bt: $(SRCS_OBJS) $(HEADERS)
	@echo "compiling $@"
	@make -C src/libft
	@cc $(SRCS_OBJS) -g $(TEST_OBJ) -Lsrc/libft -lft -o test



$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "creating $@"
	@gcc -c $(ALLFLAGS) $< -o $@

clean:
	@echo "cleaning libft"
	@make clean -C src/libft
	@rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re:fclean all
