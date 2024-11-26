%{
    #include "tokens.hpp"
%}

%option yylineno
%option noyywrap

whitespace           [\t\n\r]

print_char           [!#-\[\]-~]
/*
      !#-\[\]-~   - Printable characters from ! to ~, including punctuation, digits, and letters.
*/
ascii               \\x[0-7][0-9a-fA-F]
escape_seq          \\[ntr\"\\0]

string              ({print_char}|{ascii}|{escape_seq})

illegal_char       ([\x00-\x09\x0b\x0c\x0e-\x1f]|\x7f)

%%

void                    return VOID;
int                     return INT;
byte                    return BYTE;
bool                    return BOOL;
and                     return AND;
or                      return OR;
not                     return NOT;
true                    return TRUE;
false                   return FALSE;
return                  return RETURN;
if                      return IF;
else                    return ELSE;
while                   return WHILE;
break                   return BREAK;
continue                return CONTINUE;

;                       return SC;
,                       return COMMA;
\(                      return LPAREN;
\)                      return RPAREN;
\{                      return LBRACE;
\}                      return RBRACE;
=                       return ASSIGN;

(==|!=|<|>|<=|>=)      return RELOP;     //Checked
[\+\-\*\/]             return BINOP;     //Checked

\/\/[^\n\r]*           return COMMENT;   //Checked

[a-zA-Z][a-zA-Z0-9]*    return ID;       //Checked
(0|[1-9][0-9]*)         return NUM;      //Checked
(0|[1-9][0-9]*)+b       return NUM_B;    //Checked

(\"{string}*\")            return STRING;             //Checked

{whitespace}            ; /* ignore whitespace */
.                       return ERR_GENERAL;
\"[^\"]*                return ERR_UNCLOSED_STR;   //Checked


%%