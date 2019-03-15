#include "context.hpp"
#include <iostream>

Context::Context(){
	type_table.emplace_back();
}

void Context::register_type(std::string identifier, TypePtr type){
	type_table[0][identifier] = type;
}

TypePtr Context::resolve_type(std::string identifier){
	return type_table[0].find(identifier)->second;
}