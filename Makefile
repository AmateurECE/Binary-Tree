################################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    This is the makefile
#
# CREATED:	    11/06/2017
#
# LAST EDITED:	    11/25/2017
###

TOP:=$(PWD)
CC=gcc
CFLAGS= -g -Wall -O0 -DCONFIG_DEBUG -I$(TOP)/include/

SRCS += src/bitree.c
SRCS += src/test.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force test clean

all: force test clean

test: force $(OBJS)
	$(CC) $(CFLAGS) -o bitree $(OBJS)
	@if [ `uname` = Darwin ]; then \
		dsymutil bitree; \
	fi;

$(OBJS): force

clean:
	rm -f $(TOP)/src/test.o

force:

################################################################################
