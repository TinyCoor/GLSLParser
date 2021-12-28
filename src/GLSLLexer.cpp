//
// Created by 12132 on 2021/12/28.
//

#include "GLSLLexer.h"

token get_token(token_t type, std::string value)
{
    return (token){.type= type,.value= value};
}


std::map<char,GLSLLexer::state_dealer> GLSLLexer::funcs = {
    {'&', [](GLSLLexer* lexer)->token{
        return get_token(token_t::ampersand,"&");
    }},

    {'|', [](GLSLLexer* lexer){
        return get_token(token_t::bit_or,"|");
    }},


};
GLSLLexer::GLSLLexer(const char *file) :source(file)
{

}

void GLSLLexer::lex()
{
    while (!source.eof()) {
        auto c = next();
        if (isspace(c))
            continue;
        if (isdigit(c)) {
            lex_number();
        } else if(std::isalpha(c)){
            lex_character();
        } else{
            auto res = funcs.find(c);
            if (res != funcs.end()) {
                res->second(this);
            }
        }
    }
}
char GLSLLexer::next()
{
    source.seekg(cursor);
    cursor++;
    return source.peek();
}

std::string GLSLLexer::read_until(char c)
{
    std::string res{};
    auto wanted= next();
    while (wanted != c ) {
        res.push_back(wanted);
        wanted = next();
    }
    rewind_one_char();
    return res;
}

token GLSLLexer::lex_character()
{
    return token();
}
token GLSLLexer::lex_number()
{
    return token();
}


void GLSLLexer::rewind_one_char()
{

    source.seekg(cursor--);
}

