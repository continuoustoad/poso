#pragma once
#include <string>

namespace poso::ast
{
    enum struct node_type_t : std::uint16_t
    {
        var, num, str,
        def, fnc, app,
    };

    // I could probably implement this as a concept,
    // but I can't compile c++20 currently.
    struct node_t {
        node_type_t type;
    };

    struct var_node_t : public node_t
    {
        node_type_t type = node_type_t::var;
        std::string value;
        var_node_t(const std::string &value) : value(value) {}
    };

    struct num_node_t : public node_t
    {
        node_type_t type = node_type_t::num;
        double value;
        num_node_t(std::string value) : value(std::stod(value)) {}
    };

    struct str_node_t : public node_t
    {
        node_type_t type = node_type_t::str;
        std::string value;
        str_node_t(std::string value) : value(value) {}
    };
}
