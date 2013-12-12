
DIRSERVERSRC	= server_src/
DIRSERVEROBJ	= server_obj/
DIRSERVERINC	= server_inc/

DIRCLIENTSRC	= client_src/
DIRCLIENTOBJ	= client_obj/
DIRCLIENTINC	= client_inc/

DIRCOMMONSRC	= common_src/
DIRCOMMONOBJ	= common_obj/
DIRCOMMONINC	= common_inc/

DEBUG		= yes

ifeq ($(DEBUG), no)
		OPTI	= -Os -s
else
		OPTI	= -g
endif

CFLAGS		= -Wall \
		  -W \
		  -Wextra \
		  -Werror \
		  -I $(DIRCOMMONINC) \
		  $(OPTI)

LDFLAGSCLIENT	= -lm -lrpcsvc -lnsl -lSDL_image -lpthread \
		  -I $(DIRCOMMONINC) -I $(DIRCLIENTINC)

LDFLAGSSERVER	= -lm -lSDL_image -lpthread -lnsl \
		  -I $(DIRCOMMONINC) -I $(DIRSERVERINC)

LDFLAGSCOMMON	= -lm -lSDL_image -lpthread -lnsl \
		  -I $(DIRCOMMONINC) -I $(DIRSERVERINC) \
		  -I $(DIRCLIENTINC)

RM		= rm -f

CC		= cc

RED		= "\\033[1\;31m"

GREEN		= "\\033[32m"

YELLOW		= "\\033[33m"

BLUE		= "\\033[34m"

MAGENTA		= "\\033[35m"

CYAN		= "\\033[36m"

NOCOLOR		= "\\033[0\;0m"

ECHO		= /bin/echo -e

COMMONSRC	= $(DIRCOMMONSRC)person.c \
		  $(DIRCOMMONSRC)dataCommon.c \
		  $(DIRCOMMONSRC)infoGame.c \
		  $(DIRCOMMONSRC)xdrData.c \

CLIENTSRC	= $(DIRCLIENTSRC)main.c \

SERVERSRC	= $(DIRSERVERSRC)main.c \
		  $(DIRSERVERSRC)dataServer.c \

SERVEROBJ = $(subst $(DIRSERVERSRC),$(DIRSERVEROBJ),$(SERVERSRC:.c=.o))

CLIENTOBJ = $(subst $(DIRCLIENTSRC),$(DIRCLIENTOBJ),$(CLIENTSRC:.c=.o))

COMMONOBJ = $(subst $(DIRCOMMONSRC),$(DIRCOMMONOBJ),$(COMMONSRC:.c=.o))

SERVERNAME		= server
CLIENTNAME		= client

all:		$(CLIENTNAME) $(SERVERNAME)

$(CLIENTNAME):	$(COMMONOBJ) $(CLIENTOBJ)
	$(CC) -o $(CLIENTNAME) $(CLIENTOBJ) $(COMMONOBJ)  $(LDFLAGSCLIENT) `sdl-config --libs`
	@$(ECHO) "$(BLUE)\n$(CLIENTNAME) compiled.\n$(NOCOLOR)"

$(SERVERNAME):	$(COMMONOBJ) $(SERVEROBJ)
	$(CC) -o $(SERVERNAME) $(SERVEROBJ) $(COMMONOBJ) $(LDFLAGSSERVER) `sdl-config --libs`
	@$(ECHO) "$(BLUE)\n$(SERVERNAME) compiled.\n$(NOCOLOR)"

$(DIRCOMMONOBJ)%.o: $(DIRCOMMONSRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS) `sdl-config --libs`

$(DIRCLIENTOBJ)%.o: $(DIRCLIENTSRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGSCLIENT) `sdl-config --libs`

$(DIRSERVEROBJ)%.o: $(DIRSERVERSRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGSSERVER) `sdl-config --libs`

clean:
	@$(RM) $(COMMONOBJ) $(SERVEROBJ) $(CLIENTOBJ)
	@echo cleaning done.

fclean:	 clean
	@$(RM) $(CLIENTNAME) $(SERVERNAME)

re:	fclean all

.PHONY:	all re clean fclean
