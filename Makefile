###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    This is the makefile
#
# CREATED:	    11/06/2017
#
# LAST EDITED:	    02/12/2018
###

TOP:=$(PWD)
CC=gcc
CFLAGS= -g -Wall -O0 \
	-DCONFIG_DEBUG \
	-DCONFIG_EXTENDED_TRAVERSAL_TEST \
	-DCONFIG_MACRO_TRAVERSAL_TEST \
	-I$(TOP)/include/

SRCS += src/bitree.c
SRCS += src/test.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force test clean

all: force test

test: force $(OBJS)
	$(CC) $(CFLAGS) -o bitree $(OBJS)
	@if [ `uname` = Darwin ]; then \
		dsymutil bitree; \
	fi;
	@mv $(TOP)/src/bitree.o $(TOP)/bitree.o

$(OBJS): force

clean:
	rm -f src/*.o
	rm -f $(PWD)/*.o
	rm -f bitree
	rm -rf bitree.dSYM

force:

###############################################################################
