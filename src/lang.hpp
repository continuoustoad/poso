#pragma once
#include <map>
#include <string>
#include <forward_list>
#include <cstdlib>
#include <stack>

namespace poso::lang
{
    struct object_t
    {
        const bool has_scope = false;
        bool marked = false;
    };

    struct scope_t : public object_t
    {
        const bool has_scope = true;
        object_t *parent;
        std::map<std::string, object_t*> refs;
        object_t *operator[](const std::string &name)
        {
            if(refs.find(name) != refs.end())
                return refs[name];
            throw std::runtime_error("No such variable: " + name);
        }
    };

    using scope_stack_t = std::stack<scope_t>;

    struct number_object_t : public object_t
    { double number; };

    struct string_object_t : public object_t
    { std::size_t length; char *string; };

    // i dont like std::forward_list
    struct gc_list_t
    {
        struct cell_t
        {
            object_t *o;
            cell_t *n = nullptr;
            operator object_t*() { return o; }
            object_t *operator->() { return o; }
        };

        cell_t *head;

        gc_list_t()
        { head = new cell_t; }

        ~gc_list_t()
        {
            while(head != nullptr)
            {
                auto tmp = head->n;
                delete head;
                head = tmp;
            }
        }

        gc_list_t &operator<<(object_t *o)
        { head = new cell_t{ o, head }; return *this; }

        gc_list_t &operator>>(cell_t *o)
        { delete o->n; o->n = o->n->n;  return *this; }
    };

    class gc
    {
        gc_list_t pool;
    public:
        static gc &global_gc;

        gc &operator<<(object_t *o)
        {
            pool << o;
            return *this;
        }

        void run()
        {
            mark(*pool.head);
            sweep();
        }
    private:

        void mark(object_t *o)
        {
            if(o->marked) return;
            o->marked = true;
            if(!o->has_scope) return;
            scope_t *s = reinterpret_cast<scope_t*>(o);
            for(const auto &kv : s->refs)
                if(!kv.second->marked)
                    mark(kv.second);
        }

        void sweep()
        {
            for(gc_list_t::cell_t *x = pool.head, *p = nullptr;
                x != nullptr;
                p = x, x = x->n)
            {
                if(!(*x)->marked) pool >> p;
                else (*x)->marked = false;
            }
        }
    };

    object_t *make_number(double value)
    {
        auto x = new number_object_t;
        x->number = value;
        gc::global_gc << x;
        return x;
    }

    object_t *make_string(const std::string &s)
    {
        auto x = new string_object_t;
        x->string = const_cast<char*>(s.data());
        x->length = s.length();
        gc::global_gc << x;
        return x;
    }

    object_t *make_nil()
    {
        auto x = new object_t;
        gc::global_gc << x;
        return x;
    }
}
