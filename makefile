CXXFLAGS += -std=c++11 -w -Wall -g
CXXFLAGS += -I include

all: bin/print_canonical

bin/% : src/%.cpp
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

src/C_parser.tab.cpp src/C_parser.tab.hpp : src/C_parser.y
	bison -v -d src/C_parser.y -o src/C_parser.tab.cpp

src/C_lexer.yy.cpp : src/C_lexer.flex src/C_parser.tab.cpp
	flex -o src/C_lexer.yy.cpp src/C_lexer.flex

bin/print_canonical : src/print_canonical.o src/C_parser.tab.o src/C_lexer.yy.o src/C_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

clean :
	rm -f src/*.o
	rm -f bin/*
	rm -f src/*.tab.*
	rm -f src/*.yy.cpp
	rm -f src/*.output

parser : src/C_parser.tab.cpp src/C_parser.tab.hpp
lexer : src/C_parser.tab.hpp src/C_lexer.yy.cpp
test_lex: src/test_lexer.o src/C_lexer.yy.o src/C_parser.tab.o src/implementation/ast_function.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/test_lexer $^


