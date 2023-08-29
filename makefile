NAME := pipex

HEADERS:= inc/pipex.h

ERRFLAGS:= -Wall -Werror -Wextra
FLAGS:= -g -O0	
SRCS:= $(wildcard src/*.c)
MAIN:= main.c

OBJDIR:= obj
MAIN_OBJ:= $(MAIN:%.c=$(OBJDIR)/%.o)
SRCS_OBJS:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

ALLFLAGS:= $(ERRFLAGS) $(FLAGS)

$(NAME): $(SRCS_OBJS) $(MAIN_OBJ) $(HEADERS)
	@echo "compiling $@"
	@make -C src/libft
	@cc $(SRCS_OBJS) $(MAIN_OBJ) -Lsrc/libft -lft -o $@

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "creating $@"
	@gcc -c $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re:fclean all
