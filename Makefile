CC=clang
CXX=clang++
CFLAGS=$(O) -Wall
CXXFLAGS=$(CFLAGS) 
O=-O2
LFLAGS=-l ncurses
OBJS=objs/main.o objs/board_curses.o objs/board.o

.PHONY: all
all: objs gomoku

./gomoku: $(OBJS)
	@ echo "    LINK ./gomoku"
	@ $(CXX) $(LFLAGS) $(OBJS) -o "./gomoku"

objs/main.o: src/main.cpp src/board_curses.hpp src/board.hpp
	@ echo "    CXX  src/main.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/main.cpp" -o $@
objs/board_curses.o: src/board_curses.cpp src/board_curses.hpp src/board.hpp
	@ echo "    CXX  src/board_curses.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/board_curses.cpp" -o $@
objs/board.o: src/board.cpp src/board.hpp
	@ echo "    CXX  src/board.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/board.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./gomoku"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././gomoku

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g
debug: O=-O0
debug: CC=g++
debug: CXX=g++
debug: all

# Emacs flymake-mode
.PHONY: check-syntax
check-syntax:
	g++ $(CXXFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
