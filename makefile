# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 00:40:21 by ymarcill          #+#    #+#              #
#    Updated: 2018/05/26 21:27:54 by ymarcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ./ls_no_option.c			./ls_opt_a.c			./ls_opt_r.c\
	  ./ft_printtab.c			./ft_sort_file_dir.c	./ft_rev_params.c\
	  ./ft_sort_params.c		./main.c				./ft_rev_ou_tri.c\
	  ./ls_opt_re.c				./ls_opt_t.c			./ft_freetab.c\
	  ./ls_opt_l.c				./l_rights.c			./l_size.c\
	  ./l_name.c				./l_size2.c				./l_time.c\
	 ./l_rights_bis.c			./ls_re_opt_a.c			./ls_re_opt_r.c\
	 ./ls_re_opt_ra.c			./ls_re_opt_t.c			./ft_for_rec.c\
	 ./ls_opt_re_bis.c

OBJ = ./ls_no_option.o			./ls_opt_a.o			./ls_opt_r.o\
	  ./ft_printtab.o			./ft_sort_file_dir.o	./ft_rev_params.o\
	  ./ft_sort_params.o		./main.o				./ft_rev_ou_tri.o\
	  ./ls_opt_re.o				./ls_opt_t.o			./ft_freetab.o\
	  ./ls_opt_l.o				./l_rights.o			./l_size.o\
	  ./l_name.o				./l_size2.o				./l_time.o\
	  ./l_rights_bis.o			./ls_re_opt_a.o			./ls_re_opt_r.o\
	  ./ls_re_opt_ra.o			./ls_re_opt_t.o			./ft_for_rec.o\
	  ./ls_opt_re_bis.o

FLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJ) 
	make -C libft/
	clang $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)
#	clang $(FLAGS) -c $(SRC)

%.o: %.c
	clang $(FLAGS) -c -o $@ $^

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

clean:
	rm -rf $(OBJ)
	make clean -C libft/

re: fclean all
