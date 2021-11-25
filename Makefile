NAME	=	serveur

NAME1	=	client

NAME_B	=	serveur_bonus

NAME1_B	=	client_bonus

SRC		=	serveur.c

SRC1	=	client.c

SRC_B	=	serveur_bonus.c

SRC1_B	=	client_bonus.c

HEAD	=	minitalk.h

HEAD_B	=	minitalk_bonus.h

OBJS	= $(SRC:.c=.o)

OBJS1	= $(SRC1:.c=.o)

OBJS_B	= $(SRC_B:.c=.o)

OBJS1_B	= $(SRC1_B:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

all			:	$(NAME) $(NAME1) $(NAME_B) $(NAME1_B)

$(NAME)		:	$(OBJS)

$(NAME1)	:	$(OBJS1)

$(NAME_B)	:	$(OBJS_B)

$(NAME1_B)	:	$(OBJS1_B)

${OBJS}		:	${HEAD}

${OBJS1}	:	${HEAD}

${OBJS_B}	:	${HEAD_B}

${OBJS1_B}	:	${HEAD_B}

clean:
			$(RM) $(OBJS) $(OBJS1) $(OBJS_B) $(OBJS1_B)

fclean:		clean
			$(RM) $(NAME) $(NAME1) $(NAME_B) $(NAME1_B)

re:			fclean	all

.PHONY:		all clean fclean re