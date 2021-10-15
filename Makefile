NAME			=	philo
BONUS			=	philo_bonus

BONUS 				=   bonus

SRC_PATH			= ./srcs/
OBJ_PATH			= bin/
OBJ_BONUS_PATH		= bin/bonus/

MINILIB_PATH		= minilib/
PHILO_PATH			= philo/

CFLAGS		+=	-W -Wall -Wextra -D BUFFER_SIZE=32 -g3 #-Werror  -pedantic 		## '+=' allow to keep default flags.

ifdef WITH_BONUS
	CFLAGS	+= -DBONUS -DIF_BONUS=true

	OBJ_PATH	= $(OBJ_BONUS_PATH)
	NAME	=	$(BONUS)
else
	CFLAGS	+= -DIF_BONUS=false
endif


OBJ_PATHS_INIT			=	$(addprefix $(OBJ_PATH),$(MINILIB_PATH) 	\
													$(PHILO_PATH))
## No need for a \ on the last line
HEADERS_FILES				=	main.h
MINILIB						=	ft_atoi.c \
								ft_isdigit.c \
								ft_itoa.c \
								ft_putchar_fd.c \
								ft_putnbr_fd.c \
								ft_putstr_fd.c \
								ft_strlen.c \
								ft_strncmp.c \
								parse_value.c 

PHILO						=	clean_env.c \
								do_action.c \
								get_current_timestamp.c \
								get_forks.c \
								main.c \
								print_action.c \
								quit_philo.c \
								quit.c

SRC_FILES += $(addprefix $(MINILIB_PATH), $(MINILIB))
SRC_FILES += $(addprefix $(PHILO_PATH), $(PHILO))


OBJREGULAR_FILES	= 	$(SRC_FILES:.c=.o)  ## get all .o names from .c names


SRC		= $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ 	= $(addprefix $(OBJ_PATH), $(OBJREGULAR_FILES))

CC			=	clang

LDFLAGS		=	-pthread

RM			= 	rm -f

all					:	 $(OBJ_PATHS_INIT) $(NAME)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c $(HEADERS_FILES)
	$(CC) -o $@ -c $< $(CFLAGS)  $(INC) 

$(OBJ_PATHS_INIT)	:
	mkdir -p  $@  

$(NAME)			: 	$(OBJ) 
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)  $(INC) 

$(BONUS)		:
	$(MAKE) WITH_BONUS=1 all

clean_local		:									## delete all .o
	$(RM) -rf $(OBJ_PATH) $(OBJ_BONUS_PATH)

clean			: clean_local							## delete all .o

fclean			:	clean_local							## clean + delete executable
	$(RM) $(NAME) $(BONUS)		

re				:	fclean all							## delete all .o and recompile all. Must use when editing a .h

.PHONY			:	all bonus clean fclean re
## voir dependances plus tard 
