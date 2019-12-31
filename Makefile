CC = gcc
RM = rm -f
CFLAGS = -Wall

BIN = sshell
OBJS = functions.o main.o

all: $(BIN)

$(BIN): $(OBJS)

-include $(OBJS:.o=.d)

clean: @$(RM) *.o $(BIN) *.d core vgcore.* gmon.out

clobber: clean
