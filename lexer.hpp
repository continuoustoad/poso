#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

namespace poso::lexer
{
    enum struct token_type_t
    {
        var, num, err, eof,
        opp, clp, ops, cls,
        opc, clc, eql, str,
    };

    std::string token_type_to_str(token_type_t t)
    {
        switch(t)
        {
            case token_type_t::var: return "variable";
            case token_type_t::num: return "number";
            case token_type_t::err: return "error";
            case token_type_t::eof: return "end of file";
            case token_type_t::opp: return "opening parenthesis";
            case token_type_t::clp: return "closing parenthesis";
            case token_type_t::ops: return "opening bracket";
            case token_type_t::cls: return "closing bracket";
            case token_type_t::opc: return "opening brace";
            case token_type_t::clc: return "closing brace";
            case token_type_t::eql: return "equal sign";
            case token_type_t::str: return "string";
        }
    }

    struct token_t
    {
        token_type_t type;
        std::string value;
    };

    class token_stream_t
    {
        std::vector<token_t> buffer;
    public:
        void operator+(token_t t)
        { buffer.push_back(t); }

        token_t operator-()
        { return buffer.front(); }

        token_t operator--()
        {
            while(buffer.size() == 0) /* TODO! */;
            auto t = buffer[0];
            buffer.erase(buffer.begin());
            return t;
        }
    };

    class lex
    {
    public:
        token_stream_t token_stream;
        
        void read(std::istream &in) {}
    };

    std::istream &operator>>(std::istream &in, lex &out)
    { out.read(in); return in; }
}
