# Code Style:
## Alignment:
Alignment is pretty important, it makes
the code look a little neater.
```cpp
int   a = 0;
float b = .5f;

// ------------------ //

//      align
//      _ | _
//    /   |   \
//    v   v   v
draw( x,  y,  z);
draw(-x, -y, -z);
draw(-x,  y,  z);
// ^   ^   ^   ^^
// |    \ /    \/
//align  |     |
//     align  align

// ------------------ //

//         _    align    _          align
// align /                \           |
//   |  /                  \         / \
//   v v                   v         v v
/**/ if(fish.color == colors.yellow) x = "yay";
else if(fish.color == colors.red   ) x = "what";
else if(fish.color == colors.white ) x = "aaaa!";
else if(fish.color == colors.gree  ) x = "fish!";


//  align                 align!
//   |                      |
//   v                      v
/**/ if(magic(x) > 10) break;
else if(x.y == 3) unmagic(x);
else   { x.y = 0; x.z = 3; }; // <- made to align.
//     ^
//     |
//  these happen to align.

// unnecesary ; but looks nice.
// There is no alignment because the
// ends are on the same column. yes.
// the 'else' follows the ones before.
// (same ending column).
```

## Spaces:
* Control flow: `keyword(...)`.
  If there's only one statemnt, no `{}` are needed.
  If the statement fits, put it on the same line,
  otherwise, put it on the next line. (For else,
  having the newline is the same as for the if statement) For example:
  ```cpp
  if(!correctName())
    error("Your name is incorrect.");
  else // you could fit the statement here,
       // but it would be too close to the
       // one above, making the code harder
       // to read in my opinion. By the way,
       // don't make comments this long, because
       // you forget that (for example) the 
       // 'success' call is not by it's own...
    success("Continue...");
  return 12;
  
  // ------------------ //
  
  if(x == y) printf("hello!\n");
  else       printf("Alignment!\n");

  // ------------------ //

  if(x == z)
    while(x != y)
      /**/ if(magic(x) > 10) break;
      else if(x.y == 3) unmagic(x);
      else { error("Oh no!"); return; }
      //   ^
      //   |
      // kind of align


  ```
* Function calls:
  Function calls have the same spacing as the
  control-flow structures. `name(1, 2, 3, 4, ...);`.
  Warning! Not `name ( 1,2,3,4,... )   ;`!

* Operators
  * Commas, Semi-Colons, Colons:<br>
    * space after
    * eg. `a, b, c; n: x; case y: z;`
  * Binary operators (plus, minus, etc.)
    * space before and after.
    * eg. `a + b; c / d; a % b;`
  * Unary operators (increment, negate, etc.)
    * no spaces.
    * eg. `~a; !b; ++c; i++`
  * Parentheses / Brackets
    * no spaces.
    * eg. `data[p++]; a + (12 + b);`
  * Curly braces:
    * `{` space after; `}` space before.
    * eg. `{ .x = 1, .y = 3; }; { return a; };`
  * Ternary:
    * Space before and after `?` and `:`
    * Sometimes no space before `?`
    * eg. `a ? b : c; a? b : c;`
    * multiline: 
      ```c++
      return is_magical(69)
             ? "nice"
             : is_magical(420)
               ? "good"
               : "why?"
               ;
      ```
  * Pointer/Reference types:
    * Space before, no space after.
    * Space after const keywords.
    * eg. `int *a; int &get(const int *z);` 
  * Array types:
    * No spaces before/after `[`
    * eg. `int a[12], b[]`
## Indentation:
Indent with *tabs*.

## Newlines:
* Curly braces:
  * For C/C#/C++:
    ```c++
    int something(int a, int b)
    { return a, b; }
    // the method body is small, so 
    // you don't need newlines inside.

    cannot_do_very_sad *somethingBig()
    {
        // Comment
        int a = 0;
        while(can(a)) ++a;
        return new cannot_do_very_sad(a + 2);
    }
    ```
  * For Java/Other C-like:
    ```java
    String hello(Person p) {
        return "Hello, " + p.name;
    }
    ```

# Naming
This is about *this* C++ project. Everything is snake_case.
Also, no `const auto &very_long_variable_or_class_or_struct_or_method_or_whatever_names_please thanks;` Prefer short names, but not overly short.
So instead of `garbage_collector`, use `gc`, but not `g`.
* Types
  * Types that represent data and state: `struct name_t`
  * Types that are made to *do* something (they of course
    can have data, but the main purpose is to do something):
    `class name`
* Methods:
  * `method_name()`
* Variables
  * `int a = z + 2, b = 0;`.
  * Group variables by meaning.
    So `size_t a_len, b_len` is
    good, but `int gc_pool_size, my_grandmothers_age` isn't
    very good.
