#ifndef TOKENS_HPP
#define TOKENS_HPP

enum tokentype {
    VOID = 1,
    INT,
    BYTE,
    BOOL,
    AND,
    OR,
    NOT,
    TRUE,
    FALSE,
    RETURN,
    IF,
    ELSE,
    WHILE,
    BREAK,
    CONTINUE,
    SC,
    COMMA,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    ASSIGN,
    RELOP,
    BINOP,
    COMMENT,
    ID,
    NUM,
    NUM_B,
    STRING,
    /* Errors :) */
    ERR_UNCLOSED_STR,    /* errorUnclosedString */
    ERR_UNDEFINED_ESC,   /* errorUndefEscape    */
    ERR_GENERAL          /* errorUnknownChar    */
};

extern int yylineno;
extern char* yytext;
extern int yyleng;

extern int yylex();

#endif //TOKENS_HPP
