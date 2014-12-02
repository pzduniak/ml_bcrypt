CC = gcc
LD = gcc
PROG = ml_bcrypt.so

# Compiler flags
# NOTE: add -g for debug, remove for release!
CPPFLAGS = -m32 -MD -Wall -I./
LDFLAGS = -fPIC -m32 -shared -Wl,-soname,$(PROG).1,-R./
LIBS = -lstdc++ -llua5.1

SRCS = $(wildcard ./*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

### Make rules
all : depend ml_base

ml_base : $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(wildcard lib/blowfish/*.o) $(LIBS)

clean :
	@rm -f *.o
	@rm -f *.d
	@make -C lib/blowfish clean	

depend :
	@make -C lib/blowfish/
