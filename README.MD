# Lexical & syn analyser for regex

## Operations:

* |, *

## Rules:

S -> V S'

S' -> | V S'

S' -> eps
    
V -> K V'

V' -> K V'

V' -> * V'

V' -> eps
    
K -> C K'

K' -> eps

C -> ( E )

C -> char

## How to use

It just tests functionality: 

* g++ lexicalTest.cpp
* g++ synTest.cpp

catch.hpp - open lib-like header file from: https://github.com/catchorg/Catch2/tree/v2.x