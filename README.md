# C²
## About
This repository is to contain the compiler for a small programming language I am crafting, which is intended to be a language that shares certain Rust features, while keeping the syntax of the C programming language.
## Roadmap
I believe that in order to create the language, there must also be a working implementation of it, such as a working compiler or interpreter that can handle the designed programming language. Therefore, a large part of the development roadmap is the development of the C² compiler:
- [X] Lexer
	- The lexer chews down the raw C² source code, and produces a neat vector of the extracted tokens.
	- The extracted tokens are fed into the parser after the lexer finishes.
- [ ] Parser
	- The parser recieves the neat vector of tokens & produces a tree of objects representing the program.
	- This tree of objects that represent the program can also be known as abstract syntax tree.
- [ ] Code generation
	- This step is where low-level assembly is generated from analyzing the tree of objects that represent the program, outputted by the parser. This low-level assembly is outputted, and that's when the compiler's job finishes.
So for now, we only have the lexer finished to a point where it's usable (it just lexes regular C source code). Currently, the parser is what's being worked on.