DIROBJS = ../build
OBJS	= $(addprefix $(DIROBJS)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))
SOURCE	= main.cpp lib.cpp cmd.cpp block.cpp
HEADER	= lib.h cmd.h block.h
OUT	= ../Verlingua-Build-
NO := $(shell cat ../constructer/no)
TARGET = $(OUT)$(NO)
CC	 = clang++
FLAGS	 = -g -c -Wall -Wswitch-bool
LFLAGS	 = 

all: $(DIROBJS) $(TARGET)
	#$(CC) -g $(OBJS) -o $(OUT)$(NO) $(LFLAGS)

$(DIROBJS):
	mkdir $(DIROBJS)

$(DIROBJS)/%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@ 

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

#$(DIRSRC)/main.o: main.cpp#
	#$(CC) $(FLAGS) $(DIRSRC)main.cpp 

#lib.o: lib.cpp
#	$(CC) $(FLAGS) lib.cpp 

#cmd.o: cmd.cpp
#	$(CC) $(FLAGS) cmd.cpp 

#block.o: block.cpp
#	$(CC) $(FLAGS) block.cpp 

clean:
	rm -f $(OBJS) $(OUT)
