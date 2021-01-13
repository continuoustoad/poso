#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "lang.hpp"

poso::lang::gc x;
poso::lang::gc &poso::lang::gc::global_gc = x;

int main()
{
    poso::lexer::lex lex;
    std::cin >> lex;
    poso::parser p(lex.token_stream);

}
