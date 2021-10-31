# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 21:06:11 by rotrojan          #+#    #+#              #
#    Updated: 2021/10/31 05:00:30 by bigo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BONUS = philo_bonus


SRCS =						\
	philo_main.c			\
	philo_parsing.c			\
	philo_run.c				\
	philo_actions.c			\
	philo_routine.c			\
	philo_monitor.c			\
	$(UTILS)

UTILS =						\
	ft_atoi.c				\
	ft_atoll.c				\
	ft_strlen.c				\
	ft_putstr_fd.c			\
	get_time_now.c			\
	protected_data_utils.c	\
	msleep.c				\
	print_error.c


OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = srcs
OBJS_DIR = .objs
INCLUDES_DIR = includes

MAKE = make
MAKEFLAGS += --no-print-directory
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -Wall -Wextra -Werror -MMD -MP
ifeq ($(DEBUG), on)
	CFLAGS += -g3#-fsanitize=address
endif
LDFLAGS = -pthread

vpath %.c $(addprefix $(SRCS_DIR), /$(NAME) /$(BONUS) /utils)

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@printf '\nlinking %s\n' '$@'
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@cat .ascii_art

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR)
	@printf '\r\033[K\033[33mcompiling philo:\033[0m %s' '$@'
	@$(CC) $(CFLAGS) $(INCLUDES_DIR:%=-I %) -c $< -o $@

$(OBJS_DIR):
	@$(MKDIR) $@

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	@$(RM) $(OBJS_DIR)/debug*
	@touch $@
	@printf './objs/ removed\n'

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@printf 'philo and philo_bonus removed\n'

re: fclean all

.PHONY: all clean fclean re
