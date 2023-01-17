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