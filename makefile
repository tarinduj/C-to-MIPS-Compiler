CXXFLAGS += -std=c++17 -w -Wall -g
CXXFLAGS += -I include
CXX = g++

OBJECT_FILES += obj/run.o obj/type.o obj/chunk.o obj/context.o obj/format.o obj/posix.o
OBJECT_FILES += obj/C_lexer.o obj/C_parser.o
OBJECT_FILES += obj/ast_binop.o obj/ast_declarator.o obj/ast_function.o obj/ast_jump.o obj/ast_list.o obj/ast_node.o obj/ast_primitives.o obj/ast_translation.o obj/ast_variable.o 

TEST_OBJECT_FILES = obj/test.o

obj/format.o: 
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o obj/format.o src_fmt/format.cc

obj/posix.o: 
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o obj/posix.o src_fmt/posix.cc		

bin/test: parser lexer $(OBJECT_FILES) $(TEST_OBJECT_FILES) 
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/test $(OBJECT_FILES) $(TEST_OBJECT_FILES)

bin/c_compiler: parser lexer $(OBJECT_FILES) obj/compiler.o
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) -o bin/c_compiler $(OBJECT_FILES) obj/compiler.o 
	

obj/%.o : src/%.cpp include/*.hpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o obj/$(basename $(notdir $<)).o $< 

obj/%.o : src/%.cpp include/ast/%.hpp
	@echo building $<
	@mkdir -p obj
	@$(CXX) $(CXXFLAGS) -c -o obj/$(basename $(notdir $<)).o $< 

parser: src/C_parser.y
	@echo "building parser..."
	@bison -v -d -Wnone src/C_parser.y -o src/C_parser.tab.cpp
	@mv src/C_parser.tab.hpp include
	@mkdir -p obj
	@$(CXX) $(CXXFLAGS) -c -o obj/C_parser.o src/C_parser.tab.cpp

lexer : src/C_lexer.flex parser
	@echo "building lexer..."
	@flex -o src/C_lexer.yy.cpp src/C_lexer.flex
	@touch include/C_lexer.yy.hpp
	@mkdir -p obj
	@$(CXX) $(CXXFLAGS) -c -o obj/C_lexer.o src/C_lexer.yy.cpp

clean :
	rm -f obj/*.o
	rm -f src/*.o
	rm -f bin/*
	rm -f src/*.tab.*
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f include/C_parser.tab.hpp
	rm -f include/C_lexer.yy.hpp

test: bin/test
	bin/test


format: 
	@clang-format-6.0 -i $$(echo include/*.hpp | sed "s/include\/catch.hpp//g;s/include\/clara.hpp//g;s/include\/C_parser.tab.hpp//g;s/include\/C_lexer.yy.hpp//g") -verbose
	@clang-format-6.0 -i $$(echo src/*.cpp | sed "s/src\/C_parser.tab.cpp//g;s/src\/C_lexer.yy.cpp//g") -verbose
	@clang-format-6.0 -i $$(echo include/ast/*.hpp) -verbose

endings:
	dos2unix src/*.cpp
	dos2unix include/*.hpp
	dos2unix include/ast/*.hpp
