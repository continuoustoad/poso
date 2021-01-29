# Poso
> Note the language is not implemented yet.
> Not even the lexer/parser, the language is
> at a *very* early stage! Everything here
> is just a concept.

A concatenative language.
Here's a tutorial (? i guess):
```ruby
# For example:
a b c
# in declarative programming languages,
# this could look like this:
# c(b(a))
# Imagine this as a conveyor belt on a factory
# first 'a' goes through 'b'
# a b
# then the result of that goes through 'c'
# (a b) c

# TODO: Add the tutorial in the wiki.
# And I am too lazy to do it now, maybe
# later.

# An example of the @ operator:
12 @ 0 [10, 11] # -> [10, 11, 12]
"hello" @ :greeting [] # -> [ :x of Any = "hello" ]
#         will be fixed             ^^^
# '@' will  probably dynamically
# get the type and assign the record.

# Creates a type called Operator+
# with a single field :x of type Int
type Operator+[:x of Int]

# Creates (overloads in this case)
# a variable + of type Int to Operator+
# or a function from Int to Operator+
#  lambda argument  ____
#                       \
#                       v
+ of Int to Operator+ = { Int to Operator+
# explict type            ^^^^^^^^^^^^^^^^
# no type inference support for now.
#
#    empty record
#        |
#        |        ____ type constructor
#        |       /
#        v      V
    @ :x [] Operator+
#   ^  ^
#   |  \___ a 'keyword' 
#   |
# the @ operator (function)
};

# includes code from Stdlib/Math
# vvvvv
include :Stdlib/Math

# Creates an unnamed function
# from Operator+ to Int
from Operator+ to Int = { Operator+ to Int
    #             ___ the $ operator gets the
    #           /     element from an object.
    #          v
    x of Int = $ :x
#   ^^^^^^^^^^^^^^^
# creates a local variable x
# assigned to the :x of the
# Operator+ input.

    @ 1 [0 of Int = x] :Stdlib/Math/Add
#   ^^^^^^^^^
# creates a two element "array"
# with the first element being the x
# of the Operator+
}

# Now, how the + function works:
# For example:
# 2 + 3
# First the + function takes 2 and creates
# a Operator+[x=2]
# The the function from Operator+ to Int
# takes the 3 and adds it with 2
# finally, we get 5.
# This is how most of the infix/prefix operators
# are implemented.


# Creates a global variable x of type Int and
# initializes it with 2
x of Int = 2
y of Int = 3

# A function that does some addition.
# This is why we've implemented the +
# function/operator.
math of Int to Int = { Int to Int + x + y }

# puts is a function for outputting
# somehting to the console.

# gets is used to input something

# the Int constructor can convert a
# string to an integer

# To use puts we need to convert the
# integer result of math to a string.
# the Str constructor is used for that.
gets Int math Str puts

```

## Currently Implemented / TODO
### Compiler (For now, Temporary Evaluator)
- [x] Lexer (Both)
- [ ] Parser (Both)
- [ ] Type-checker (Compiled)
- [ ] Temporary Evaluator
- [ ] Optimiser? (Compiled)

### VM
- [ ] Bytecode Spec
- [ ] Bytecode Reader
- [ ] Bytecode Evaluator
- [ ] AOT/JIT? (very improbable)
