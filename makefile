CXXFLAGS += -std=c++17 -w -Wall -g
CXXFLAGS += -I include
CXX = g++-8

OBJECT_FILES = obj/run.o
TEST_OBJECT_FILES = obj/test.o

bin/test: parser lexer $(OBJECT_FILES) $(TEST_OBJECT_FILES) 
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/test $(OBJECT_FILES) $(TEST_OBJECT_FILES)

bin/compiler: parser lexer $(OBJECT_FILES) obj/compiler.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/compiler $(OBJECT_FILES) obj/compiler.o 
	

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

test: bin/test
	bin/test

format: 
	clang-format-6.0 -i $$(echo include/*.hpp | sed "s/include\/catch.hpp//g;s/include\/clara.hpp//g;s/include\/C_parser.tab.hpp//g;s/include\/C_lexer.yy.hpp//g") -verbose
	clang-format-6.0 -i $$(echo src/*.cpp | sed "s/src\/C_parser.tab.cpp//g;s/src\/C_lexer.yy.cpp//g") -verbose


