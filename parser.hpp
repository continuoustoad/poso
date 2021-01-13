#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "lexer.hpp"
#include "ast.hpp"
#define RET_NODE(t, v) {  }

namespace poso
{
    enum struct error_type_t
    {
        expected,
        unexpected,
        assertion,
        other,
    };

    class parser
    {
        lexer::token_stream_t &in;

        void error(error_type_t type, const std::string &msg, bool fatal = false)
        {
            if(fatal) std::cerr << "[Fatal] ";
            std::cerr << "Error: ";
            switch(type)
            {
                case error_type_t::expected: std::cerr << "Expected "; break;
                case error_type_t::unexpected: std::cerr << "Unxpected "; break;
                case error_type_t::assertion: std::cerr << "Assertion failed: "; break;
                default: break;
            }
            std::cerr << msg << std::endl;
            if(fatal) exit(1);
        }

        void assert_fatal(bool cond, const std::string &msg)
        {
            if(!cond) error(error_type_t::assertion, msg, true);
        }

        bool check(lexer::token_type_t tok)
        { return (-in).type == tok; }

        lexer::token_t expect(lexer::token_type_t tok) 
        {
            if(!check(tok))
                return error(error_type_t::expected, lexer::token_type_to_str(tok)),
                       (lexer::token_t){ tok, "" };
            else return --in;
        }

        lexer::token_t expect(std::initializer_list<lexer::token_type_t> toks)
        {
            assert_fatal(toks.size() != 0, "Multi-Expect length not 0 for type array.");
            for(const auto &tok : toks)
                if(check(tok)) { return --in; }
            std::ostringstream s("one of: ");
            for(const auto &tok : toks)
                s << lexer::token_type_to_str(tok);
            error(error_type_t::expected, s.str());
            return { *toks.begin(), "" };
        }

        ast::node_t *parse_atom()
        {
            auto t = expect({ lexer::token_type_t::var,
                              lexer::token_type_t::num,
                              lexer::token_type_t::str,
                              lexer::token_type_t::opp, });
            if(t.type == lexer::token_type_t::var)
            { return new ast::var_node_t(t.value); }
            else error(error_type_t::expected, "an atom");
            return new ast::var_node_t("<error>");
        }
    public:
        parser(lexer::token_stream_t &in) : in(in) {}
    };
}
