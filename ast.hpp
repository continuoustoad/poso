#pragma once
#include <string>
#include "lang.hpp"

namespace poso::ast
{
    struct node_t { virtual lang::object_t * eval(lang::scope_t&) = 0; };

    struct var_node_t : node_t
    {
        std::string value;
        var_node_t(const std::string &value) : value(value) {}
        virtual lang::object_t *eval(lang::scope_t &sc) { return sc[value]; }
    };

    struct num_node_t : node_t
    {
        double value;
        num_node_t(std::string value) : value(std::stod(value)) {}
        virtual lang::object_t *eval(lang::scope_t &sc) { return lang::make_number(value); }
    };

    struct str_node_t : node_t
    {
        std::string value;
        str_node_t(std::string value) : value(value) {}
        virtual lang::object_t *eval(lang::scope_t &sc) { return lang::make_string(value); }
    };
}
