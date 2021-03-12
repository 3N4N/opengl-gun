# Tic Tac Toe

CC     = g++
CFLAGS = -g -w -Iinc/
LIBS   = -lGL -lGLU -lglut

SRCS   = $(wildcard src/*.cpp)
OBJS   = $(patsubst src/%.cpp,bin/%.o,$(SRCS))
DEPS   = $(OBJS:.o:=.d)
DIRS   = src inc bin
EXE    = a.out

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

bin/%.o : src/%.cpp
	$(CC) -o $@ $(CFLAGS) -c $<

bin/%.o : src/%.cpp inc/%.h
	$(CC) -o $@ $(CFLAGS) -c $<

run : all
	./$(EXE)

clean:
	rm -rf bin *~ $(EXE)
