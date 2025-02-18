
PARSING
It's a program or a programming component that analyzes code according to CFG and creates an AST.
Parser's tatsks:
1. Checking syntax: veryfining if the input corresponds the grammar rules
2. Creating from tokens an AST that can be processed programmatically





AST
Abstract Syntax Tree.
It's a code structure. It shows the logic and connections of code's elements in a tree representation.
And AST considers order and nesting of operstions.

The tree has:
*ATS nodes - operators, expressions, functions
*AST leaves - variables, constants

How AST works:
1. Code contains operators(if, while, for ...), expressions(a+b, x*2 ...), variables, functions and classes
2. Parser creates AST to show how those elements are connected.





CFG
Context Free Grammar.
Using to parse source code to create AST. It descripts syntax structure of programming languages.
It's rules explain how symbols can be changed to another symbols.

Type of symbols:
1. Terminal symbols - terminal symbols of language:
        * key words( if, else, while, for)
        * operators (+, -, *, /)
        * numbers and strings
        * symbols( (, ), {, }, ;, ...)
2. Non-terminal symbols - expression, termin and factor.
You may think about it in this way: expression is a sentence, termins are words is the sentence, factors - letters in words.

CFG production rules:
1. Define how to change non-terminal symbols into anothe symbols or symbols sequence.
2. The rule looks like: A -> a:
        * "A" is a non-terminal symbol. It's aslo a start symbol.
        * "a" can be a string of terminal and non-terminal symbols.
3. It's a symbol from there the generation process starts.





PRECEDENCE CLIMBING
Precedence climbing is a parsing technique that can be used for the correct interpretation of expressions with operators within grammars such as context-free grammars.
The simpliest algorithm for expression parsing. It treats an expression as a brunch of nested sub-expressions.
Each sub-expression has in common the lowest precedence level of the operators it contains.

Here's a simple example:
1. 2 + 3 * 4 * 5 - 6
   Assuming that the precedence of + (and -) is 1 and the precedence of * (and /) is 2, we have:
2. 2 + 3 * 4 * 5 - 6

   |---------------|   : prec 1
       |-------|       : prec 2