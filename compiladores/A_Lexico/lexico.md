# Analisador Léxico

1. Tirar todos os espaços em branco
2. Tirar todos os comentários

[(\(.*\*\))]


- Categorias:
    letras: a,b,c,d,e...,
    Dígitos: 0-9,
    Simbolos especiais: >, =, <, +,-, *, /
    Simbolos especiais compostos: <>, :=, >=, <=,
    Palabra Reservada: program, label, type, of, var, procedure, begin, end, if, then, else, while, do, or, and, not;

ENUM tokens_identificadores {
    LETRA,
    DIGITO,
    SIMBOLO_ESPECIAL,
    COMPOSTO_ESPECIAL,
    KEYWORD
}
