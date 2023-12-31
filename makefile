PLATFORM = djgpp
CC = gcc
EXE = .exe
OBJ = .o
AR = ar

PLATFORM_DIR = obj/djgpp

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
OFLAGS = $(TARGET_ARCH) $(TARGET_OPTS) -fgnu89-inline
LIB_NAME = ./lib/djgpp/libjgmod.a

BIN_DIR = ./bin
OBJ_DIR = ./obj/djgpp
OBJ_LIST = \
	$(OBJ_DIR)/file_io.o \
	$(OBJ_DIR)/load_mod.o \
	$(OBJ_DIR)/load_s3m.o \
	$(OBJ_DIR)/load_xm.o \
	$(OBJ_DIR)/load_it.o \
	$(OBJ_DIR)/load_jgm.o \
	$(OBJ_DIR)/save_jgm.o \
	$(OBJ_DIR)/mod.o \
	$(OBJ_DIR)/player.o \
	$(OBJ_DIR)/player2.o \
	$(OBJ_DIR)/player3.o \
	$(OBJ_DIR)/player4.o

lib:

	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/file_io.c -o $(OBJ_DIR)/file_io.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/load_mod.c -o $(OBJ_DIR)/load_mod.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/load_s3m.c -o $(OBJ_DIR)/load_s3m.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/load_xm.c -o $(OBJ_DIR)/load_xm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/load_it.c -o $(OBJ_DIR)/load_it.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/load_jgm.c -o $(OBJ_DIR)/load_jgm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/save_jgm.c -o $(OBJ_DIR)/save_jgm.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/mod.c -o $(OBJ_DIR)/mod.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/player.c -o $(OBJ_DIR)/player.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/player2.c -o $(OBJ_DIR)/player2.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/player3.c -o $(OBJ_DIR)/player3.o
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -c ./src/player4.c -o $(OBJ_DIR)/player4.o

	ar rs $(LIB_NAME) $(OBJ_LIST)

	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) ./src/jgmod.c -o $(BIN_DIR)/jgmod.exe -s $(LIB_NAME) -lalleg
	$(CC)  $(WFLAGS) $(OFLAGS) -I$(HEADERS) -L$(ALLEGRO) ./src/jgm.c -o $(BIN_DIR)/jgm.exe -s $(LIB_NAME) -lalleg
