CXXFLAGS += -std=c++17 -w -Wall -g
CXXFLAGS += -I include
CXX = g++-8

OBJECT_FILES = obj/run.o

bin/test: parser lexer $(OBJECT_FILES) obj/test.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/test

bin/test: parser lexer $(OBJECT_FILES) obj/compiler.o
	mkdir -p bin
	bin/test

obj/%.o : src/%.cpp include/%.hpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o obj/$(basename $(notdir $<)).o $< 


parser: src/C_parser.y
	bison -v -d src/C_parser.y -o src/C_parser.tab.cpp 
	mv src/C_parser.tab.hpp include

lexer : src/C_lexer.flex parser
	flex -o src/C_lexer.yy.cpp src/C_lexer.flex
	touch include/C_lexer.yy.hpp

bin/print_canonical : src/print_canonical.o src/C_parser.tab.o src/C_lexer.yy.o src/C_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

clean :
	rm -f obj/*.o
	rm -f src/*.o
	rm -f bin/*
	rm -f src/*.tab.*
	rm -f src/*.yy.cpp
	rm -f src/*.output
