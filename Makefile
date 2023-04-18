# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 11:49:16 by myanez-p          #+#    #+#              #
#    Updated: 2023/04/18 17:06:10 by myanez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Dossiers

SRCDIR = srcs
OBJDIR = objs/
HDRDIR = includes

# Fichiers

SRCS = $(shell find ${SRCDIR} -name '*.c')
OBJS = ${SRCS:${SRCDIR}%.c=${OBJDIR}%.o}
HEADERS = ${HDRDIR}

# Compilation

GCC = GCC
CFLAGS = -Wall -Wextra -Werror

# Commandes

MKDIR = mkdir
RM = rm -Rf

# Règles

all : server client

server : ${OBJS}
	@${GCC} ${CFLAGS} -I ${HEADERS} objs/server.o -Llibft -lft -o server
	
client : ${OBJS}
	@${GCC} ${CFLAGS} -I ${HEADERS} objs/client.o -Llibft -lft -o client

${OBJDIR}%.o : ${SRCDIR}%.c
	@${MKDIR} -p ${OBJDIR}
	@if [ ! -f libft/libft.a ]; then make -C libft; fi
	@${GCC} ${CFLAGS} -I ${HEADERS} -c $< -o $@

# Nettoyage

clean : 
		@make clean -C libft
		@${RM} ${OBJS}
		@${RM} ${OBJDIR}

fclean :	clean
			@make fclean -C libft
			@${RM} server
			@${RM} client

# Autres règles

re : fclean all

.PHONY: re fclean clean all