# mingw specific makefile

include makefile.clang

# set up all the variables used in the main makefile

CP                   = cp
RM                   = rm -f
MKDIR                = mkdir
RMDIR                = rm -rf

AR                   = ar

EXAMPLE_LIBS         = $(LIB_STATIC) -lNL -lncurses

LDFLAGS             += -L/Users/david/development/ext/src/boost_1_44_0/stage/lib -L/Users/david/development/ext/src/HawkNL1.68/src

LIB_STATIC           = lib/mingw/$(LIB_STATIC_NAME)

EXE_MASK             = examples/%.exe

EXAMPLE_EXE          = $(addprefix examples/,$(notdir $(EXAMPLE_O:.o=.exe)))

LIBDIR               = $(MINGDIR)\lib\\

INCDIR               = $(MINGDIR)\include\\
