//#include "../include/ast.hpp"
extern int yylex(void);
#include <iostream>
#include <map>
#include <string>

std::map<int, std::string> m = {
    {258, "T_IDENTIFIER"},   {259, "T_STRINGLIT"},  {260, "T_SIZEOF"},
    {261, "T_FLOATCONST"},   {262, "T_INTCONST"},   {263, "T_INC"},
    {264, "T_DEC"},          {265, "T_LEFT_OP"},    {266, "T_RIGHT_OP"},
    {267, "T_LE"},           {268, "T_GE"},         {269, "T_EQ"},
    {270, "T_NE"},           {271, "T_ARROW"},      {272, "T_AND"},
    {273, "T_OR"},           {274, "T_MUL_ASSIGN"}, {275, "T_DIV_ASSIGN"},
    {276, "T_MOD_ASSIGN"},   {277, "T_ADD_ASSIGN"}, {278, "T_ASSIGN"},
    {279, "T_OR_ASSIGN"},    {280, "T_SUB_ASSIGN"}, {281, "T_LEFT_ASSIGN"},
    {282, "T_RIGHT_ASSIGN"}, {283, "T_AND_ASSIGN"}, {284, "T_AND_L"},
    {285, "T_OR_L"},         {286, "T_DOT"},        {287, "XOR_ASSIGN"},
    {288, "OR_ASSIGN"},      {289, "T_TYPEDEF"},    {290, "T_EXTERN"},
    {291, "T_STATIC"},       {292, "T_AUTO"},       {293, "T_REGISTER"},
    {294, "T_CHAR"},         {295, "T_INT"},        {296, "T_UNSIGNED"},
    {297, "T_VOID"},         {298, "T_LONG"},       {299, "T_SIGNED"},
    {300, "T_VOLATILE"},     {301, "T_FLOAT"},      {302, "T_DOUBLE"},
    {303, "T_STRUCT"},       {304, "T_ENUM"},       {305, "T_UNION"},
    {306, "T_ELLIPSIS"},     {307, "T_CASE"},       {308, "T_DEFAULT"},
    {309, "T_IF"},           {310, "T_ELSE"},       {311, "T_SWITCH"},
    {312, "T_WHILE"},        {313, "T_DO"},         {314, "T_FOR"},
    {315, "T_GOTO"},         {316, "T_CONTINUE"},   {317, "T_BREAK"},
    {318, "T_RETURN"},       {319, "T_PLUS"},       {320, "T_STAR"},
    {321, "T_DIV"},          {322, "T_MOD"},        {323, "T_CONST"},
    {324, "T_CHARCONST"},    {325, "T_G"},          {326, "T_L"},
    {327, "T_MINUS"},        {328, "T_SHORT"},      {329, "T_TILDE"},
    {330, "T_TYPE_NAME"},    {331, "T_XOR"},        {332, "T_XOR_ASSIGN"},
    {333, "T_EXCL"}};

int main() {

  while (1) {
    int token = yylex();
    std::cout << m[token] << std::endl;
  };

  return 0;
}