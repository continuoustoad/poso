#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <def.hpp>

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
        void operator<<(token_t t)
        {
            std::cout << "+token: "
                << token_type_to_str(t.type) << ": '"
                << t.value << "'" << std::endl;
            buffer.push_back(t);
        }

        token_t operator-()
        { return buffer.front(); }

        token_t operator--()
        {
            auto t = buffer[0];
            buffer.erase(buffer.begin());
            return t;
        }
    };

    class lex
    {
    public:
        token_stream_t token_stream;
        
        void read(std::istream &in)
        {
            while(in.peek() != EOF && in.peek() != '\n')
            {
                auto x = in.peek();
                std::cout << "Read, " << (char)x << ", " << (int)x << std::endl;
                /**/ if(is_space(x))
                    {Q_(s)in.get(); }
                else if(is_number(x))
                    {Q_(n)read_number(in); }
                else if(is_string(x))
                    {Q_(s)read_string(in);}
                else if(is_special(x)) // order matters!
                    {Q_(p)read_special(in);}
                else if(is_valid(x)) // valid includes special 
                    {Q_(v)read_valid(in);}
                else
                    unknown_char(in);
            }
        }
    private:
        void read_number(std::istream &in)
        {
            std::string s;
            while(is_number(in.peek()))
                s += in.get();
            token_stream << token_t{ token_type_t::num, s };
        }

        void read_string(std::istream &in)
        {
            std::string s;
            in.get(); // skip '"'
            while(!is_string(in.peek()))
                s += in.get();
            in.get(); // skip '"'
            token_stream << token_t{ token_type_t::str, s };
        }

        void read_special(std::istream &in)
        {
            static std::map<char, token_type_t> type_map =
            {
                { '(', token_type_t::opp },
                { ')', token_type_t::opp },
                { '[', token_type_t::ops },
                { ']', token_type_t::ops },
                { '{', token_type_t::opc },
                { '}', token_type_t::clc },
                { '=', token_type_t::eql },
            };
            token_stream << token_t{ type_map[in.get()], "" };
        }

        void read_valid(std::istream &in)
        {
            std::cout << "read_valid" << std::endl;
            std::string s;
            char c = 0; 
            while(is_valid(c = in.peek()))
            {
                std::cout << c << ", " << (int)c << std::endl;
                s += in.get();
            }
            std::cout << c << ", " << (int)c << std::endl;
            token_stream << token_t{ token_type_t::var, s };
        }

        void unknown_char(std::istream &in)
        {
            std::cerr << "Unknown character: '"
                << in.get() << "'" << std::endl;
        }

        bool is_number (int x) { return std::isdigit(x); }
        bool is_space  (int x) { return std::isspace(x); }
        bool is_string (int x) { return x == '"'; }
        bool is_valid  (int x) { return std::isgraph(x); }
        bool is_special(int x)
        {
            static auto special_tokens = "()[]{}=";
            return std::find(special_tokens, special_tokens + 8, x) != special_tokens + 8;
        }
    };

    std::istream &operator>>(std::istream &in, lex &out)
    { out.read(in); return in; }
}
