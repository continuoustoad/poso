#pragma once
#include <lang.hpp>
#include <ast.hpp>

namespace poso
{
    class eval
    {
        friend parser &operator>>(parser&, eval&);
        lang::scope_stack_t scope_stack;


        lang::object_t *run_node(ast::node_t *n)
        {  
            auto &runtime_error = std::cerr;
            if(!n)
            {
                runtime_error << "Nil node." << std::endl;
                return lang::make_nil();
            }
#define nt(t) ((ast::t##_node_t*)n)
            switch(n->type)
            {
                case ast::node_type_t::var:
                    return scope_stack.top()[nt(var)->value];
                case ast::node_type_t::num:
                    return lang::make_number(nt(num)->value);
                case ast::node_type_t::str:
                    return lang::make_string(nt(str)->value);
                default:
                    runtime_error << "Node with type "
                        << ((int)n->type)
                        << " not implemented!" << std::endl;
                    break;
            }
            return nullptr;
        }
     public:
        int exit_code = 0;
    };

    parser &operator>>(parser &in, eval &out)
    {
        out.run_node(in.root);
        return in;
    }
}
