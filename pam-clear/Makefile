#
# Makefile
#
VERSION=0.1

CC=gcc
CFLAGS = -O -g -W -Wall -Wno-unused-result -fPIC
#CFLAGS = -O -ggdb -W -Wall -Wno-unused-result -fPIC
#CFLAGS = -O2 -g -Wall -Wformat-security
#CFLAGS = -fPIC -fvisibility=hidden
CPPFLAGS =

TITLE = pam_clear
## -Wl,options #this is to pass options to Linker when called indirectly,
## and this implies that LDFLAGS should appear first. -x I think no language specified
## no space after -Wl,
LDFLAGS = -Wl,-x -shared
LDLIBS = -lpam
#PAMLIB=/lib/security
PAMLIB=/lib/x86_64-linux-gnu/security

all: $(TITLE).so

$(TITLE).so: $(TITLE).o
	$(CC) $(LDFLAGS) $(TITLE).o $(LDLIBS) -o $@

$(TITLE).o: src/$(TITLE).c
	$(CC) -c  $(CPPFLAGS) $(CFLAGS) $? -o $@

# @ Stops line from being echoed
clean:
	@#rm -f $(TARGETS) *~ *.o core
	$(RM) *~ *.o *.so core

