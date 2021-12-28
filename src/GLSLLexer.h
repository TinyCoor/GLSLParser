//
// Created by 12132 on 2021/12/28.
//

#ifndef GLSLPARSER_SRC_GLSLLEXER_H
#define GLSLPARSER_SRC_GLSLLEXER_H
#include <queue>
#include <fstream>
#include <string>
#include <functional>
#include <map>
enum class token_t {
    macro,
    comma,
    slash,          /// '\'
    plus,
    sub,
    ampersand,     /// '&'
    bit_or,        /// '|'
    bit_xor,
    logic_and,
    logic_or,
    unknown,

};


struct token {
    token_t type;
    std::string value;
};


class GLSLLexer {
public:
    using state_dealer = std::function<token(GLSLLexer*)>;
    GLSLLexer(const char* file);


    void lex();

private:
   char next();
   std::string read_until(char c);
   token lex_character();
   void rewind_one_char();

   token lex_number();

private:
    std::ifstream  source;
    uint32_t cursor =0;
    std::queue<token> tokens{};
    static std::map<char,state_dealer> funcs;
};

#endif //GLSLPARSER_SRC_GLSLLEXER_H
