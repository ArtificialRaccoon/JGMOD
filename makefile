PLATFORM = djgpp
CC = gcc
EXE = .exe
OBJ = .o
AR = ar

PLATFORM_DIR = obj/djgpp

OBJ_DIR = obj/djgpp/$(VERSION)
LIB_NAME = lib/djgpp/lib$(VERSION).a

ifdef CROSSCOMPILE
   UNIX_TOOLS = 1
   CC = $(XPREFIX)gcc
   AR = $(XPREFIX)ar
endif

ifneq (,$(findstring bash,$(SHELL)))
   UNIX_TOOLS = 1
endif



# -------- autodetect whether to use LFN --------

ifdef CROSSCOMPILE
   HTML = html
   INFO = info
   TEXI = texi
else
ifeq ($(LFN),y)
   HTML = html
   INFO = info
   TEXI = texi
else
   HTML = htm
   INFO = inf
   TEXI = txi
endif
endif



# -------- run some sanity checks on the djgpp installation --------

.PHONY: baddjgpp baddjdev badgcc badbnu badmake badtxi badpath badalleg lib



# -------- check that the DJGPP environment variable is set --------

ifndef DJDIR
baddjgpp:
	@echo Your DJGPP environment variable is not set correctly! It should
	@echo point to the djgpp.env file: see the djgpp readme.1st for details.
endif

DJDIR_U = $(subst \,/,$(DJDIR))
DJDIR_D = $(subst /,\,$(DJDIR))


WFLAGS = -Wall -Wno-unused
TARGET_ARCH = -march=i386 -m80387 -mtune=pentium
TARGET_OPTS = -O3 -funroll-loops -ffast-math -fomit-frame-pointer
HEADERS = ./allegro/include
ALLEGRO = ./allegro/lib/djgpp
OFLAGS = $(TARGET_ARCH) $(TARGET_OPTS)

include makefile.lst

lib:
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/file_io.c -o ./obj/djgpp/file_io.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/load_mod.c -o ./obj/djgpp/load_mod.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/load_s3m.c -o ./obj/djgpp/load_s3m.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/load_xm.c -o ./obj/djgpp/load_xm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/load_it.c -o ./obj/djgpp/load_it.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/load_jgm.c -o ./obj/djgpp/load_jgm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/save_jgm.c -o ./obj/djgpp/save_jgm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/mod.c -o ./obj/djgpp/mod.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/player.c -o ./obj/djgpp/player.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/player2.c -o ./obj/djgpp/player2.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/player3.c -o ./obj/djgpp/player3.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/player4.c -o ./obj/djgpp/player4.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/jgmod.c -o ./obj/djgpp/jgmod.exe
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) -lalleg -c ./src/jgm.c -o ./obj/djgpp/jgm.exe
