#include <lexer.hpp>
#include <parser.hpp>
#include <ast.hpp>
#include <lang.hpp>
#include <eval.hpp>
#include <def.hpp>

poso::lang::gc x;
poso::lang::gc &poso::lang::gc::global_gc = x;

int main()
{
    poso::lexer::lex lex;
    LOG("lex start:")
    std::cin >> lex;
    LOG("lex end.")
    
    LOG("parse start:")
    poso::parser par;
    lex >> par;
    LOG("parse end.")
    
    LOG("eval start:")
    poso::eval eval;
    par >> eval;
    LOG("eval end.")

    return eval.exit_code;
}
