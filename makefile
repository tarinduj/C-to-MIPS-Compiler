CXXFLAGS += -std=c++11 -w -Wall -g
CXXFLAGS += -I include

all: bin/print_canonical

bin/% : src/%.cpp
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

src/C_parser.tab.cpp src/C_parser.tab.hpp : src/C_parser.y
	bison -v -d src/C_parser.y -o src/C_parser.tab.cpp

src/C_lexer.yy.cpp : src/C_lexer.flex src/C_lexer.tab.hpp
	flex -o src/C_lexer.yy.cpp  src/C_lexer.flex

bin/print_canonical : src/print_canonical.o src/C_parser.tab.o src/C_lexer.yy.o src/C_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp
