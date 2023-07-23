SRC_FILE =  fonction_aid/ft_split.c fonction_aid/ft_strjoin.c fonction_aid/ft_strncmp.c fonction_aid/ft_strlen.c \
				fonction_aid/ft_strdup.c fonction_aid/ft_patht.c fonction_aid/concat.c G_N_L/get_next_line.c \
					G_N_L/get_next_line_utils.c herdoc/creat_linkdlist.c herdoc/herd_1.c herdoc/herd_2.c \
							redir/creat_cmd.c redir/file_redir.c redir/child_redir.c make_pip.c mini_shell.c
NAME = mini_shell
OBJ_FILE = $(SRC_FILE:.c=.o)
CFLAGS = #-Wall -Werror -Wextra
HEADER = mini_shell.h
cc = gcc

all : $(NAME)

%.o:%.c $(HEADER)
	$(cc) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ_FILE) 
	@$(cc) $(CFLAGS) $(OBJ_FILE) -o $(NAME)

clean :
	rm -f $(OBJ_FILE)

fclean : clean
	rm -f $(NAME)

re : fclean all
