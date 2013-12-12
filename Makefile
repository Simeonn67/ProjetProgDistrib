
DIRSERVERSRC	= server_src/
DIRSERVEROBJ	= server_obj/
DIRSERVERINC	= server_inc/

DIRCLIENTSRC	= client_src/
DIRCLIENTOBJ	= client_obj/
DIRCLIENTINC	= client_inc/

DIRCOMMONSRC	= common_src/
DIRCOMMONOBJ	= common_obj/
DIRCOMMONINC	= common_inc/
DIREXTLIBSINC	= extlibs/include/

DEBUG		= no

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

LDFLAGSCLIENT	= -lrpcsvc -lnsl -lSDL_image -lpthread \

LDFLAGSSERVER	= -lSDL_image -lpthread -lnsl \

LDFLAGSCOMMON	= -lSDL_image -lpthread -lnsl \

RM		= rm -f

CC		= gcc

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

CLIENTSRC	= $(DIRCLIENTSRC)main.c \
		  $(DIRCLIENTSRC)data.c \


SERVERSRC	= $(DIRSERVERSRC)dataServer.c \

SERVEROBJ = $(subst $(DIRSERVERSRC),$(DIRSERVEROBJ),$(SERVERSRC:.cpp=.o))

CLIENTOBJ = $(subst $(DIRCLIENTSRC),$(DIRCLIENTOBJ),$(CLIENTSRC:.cpp=.o))

COMMONOBJ = $(subst $(DIRCOMMONSRC),$(DIRCOMMONOBJ),$(COMMONSRC:.cpp=.o))

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
