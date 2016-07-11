LIB=		9p
SHLIB_MAJOR=	1
SRCS=		pack.c \
		connection.c \
		request.c log.c \
		hashtable.c \
		utils.c \
		rfuncs.c \
		transport/socket.c \
		backend/fs.c \
		client.c

INCS=		lib9p.h
CC=clang
CFLAGS=		-g -O2 -DL9P_DEBUG=L9P_DEBUG
# Note: to turn on debug, use -DL9P_DEBUG=L9P_DEBUG

LIBADD=		sbuf
SUBDIR=		example

cscope: .PHONY
	cd ${.CURDIR}; cscope -buq $$(find . -name '*.[ch]' -print)

.include <bsd.lib.mk>
