################################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    This is the makefile
#
# CREATED:	    11/06/2017
#
# LAST EDITED:	    11/14/2017
###

TOP:=$(PWD)
CC=gcc
CFLAGS= -g -Wall -O0 \
	-DCONFIG_DEBUG \
	`if [ \`uname\` = Darwin ]; then \
		echo -DPASS='"\033[1;32m"'; \
	fi; ` # On my home machine, this is the correct terminal sequence

SRCS += src/bitree.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force clean

all: force bitree clean

bitree: force $(OBJS)
	$(CC) $(CFLAGS) -o bitree $(OBJS)
	@if [ `uname` = Darwin ]; then \
		dsymutil bitree; \
	fi;

$(OBJS): force

clean:
	rm -f $(TOP)/src/*.o
	rm -f $(TOP)/src/*.c~
	rm -f $(TOP)/src/*.h~

force:

################################################################################
