####################################################
#                                                  #
#     JGMOD examples by Guan Foo Wah               #
#                                                  #
####################################################


CFLAGS = -O3  -W -Wno-unused -Wall -mcpu=pentium -s -ffast-math -fomit-frame-pointer -funroll-loops
LDLIBS = -ljgmod `allegro-config --libs`

examples = ex1 ex2 ex3 ex4 ex5 ex6 ex7

all : $(examples)
	@echo Finished compiling. 
	@echo To compress exes, type make compress

ex% : ex%.o
ex%.o: ex%.c

clean :
	rm ex?

compress: $(examples)
    ifneq ($(DJP),)
	@$(DJP) $(examples)
    else
	@echo No executable compressor found! This target requires either the
	@echo DJP or UPX utilities to be installed.
    endif


