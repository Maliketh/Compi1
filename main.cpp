#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>

#define MAX_STRING_LEN 


/* =========  Helper function - in the feuture maybe move to a new file   =========*/

/* lexeme is the value of the token.
   yylineno is a global variable provided by Flex  that keeps track of the current line number being processed in the input stream. */
void printToken (const char* name, const char* lexeme ) 
{
    std::cout << yylineno << " " << name << " " << lexeme << std::endl;
}

/* yyleng represents the number of characters in the current match, excluding the null terminator.*/
void printString ()
{
    std::string output = "";

    /* Skip the first and last index to avoid  "" */
    for (int i = 1; i < yyleng - 1; i++)
    {
        if (yytext[i] == '\\') 
        {
            char cur_char = yytest[++i];

            switch (cur_char)
            {
                case 'n':
                    output.pushback ('\n');
                    break;

                case 'r':
                    output.pushback('\r');
                    break;

                case 't':
                    output.pushback('\t');
                    break;

                case '\\':
                    output.pushback('\\');
                    break;

                case '"':
                    output.pushback('\"');
                    break;

                case 'x':
                    std::string ascii_val "";
                    ascii_val.append (&yytext[++i], 2);
                    int hexValue = std::stoi (ascii_val.lower(), nullptr, 16);
                    char val  = static_cast<char> (hexValue);
                    output.pushback (val);
                    i++;

            }

        }
        else 
        {
            output.pushback (yytext[i]);
        }
    }

    std::cout << yylineno << " " << "STRING" << " " << output << std::endl;
}



/* ==========================  End of helper functions   ==========================*/

/* yytext is a global variable provided by Flex that contains the text of the current token that was matched by the lexer.
   It points to a null-terminated string representing the input that corresponds to the pattern in your Flex rules.*/

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) 
    {
        switch (token)
        {
            case VOID:
                printToken ("VOID", yytext);
                break;

            case INT:
                printToken ("INT", yytext);
                break;

            case BYTE:
                printToken ("BYTE", yytext);
                break;

            case BOOL:
                printToken ("BOOL", yytext);
                break;

            case AND:
                printToken ("AND", yytext);
                break;

            case OR:
                printToken ("OR", yytext);
                break;

            case NOT:
                printToken ("NOT", yytext);
                break;

            case TRUE:
                printToken ("TRUE", yytext);
                break;

            case FALSE:
                printToken ("FALSE", yytext);
                break;

            case RETURN:
                printToken ("RETURN", yytext);
                break;

            case IF:
                printToken ("IF", yytext);
                break;

            case ELSE:
                printToken ("ELSE", yytext);
                break;

            case WHILE:
                printToken ("WHILE", yytext);
                break;

            case BREAK:
                printToken ("BREAK", yytext);
                break;


            case CONTINUE:
                printToken ("CONTINUE", yytext);
                break;

            case SC:
                printToken ("SC", yytext);
                break;

            case COMMA:
                printToken ("COMMA", yytext);
                break;

            case LPAREN:
                printToken ("LPAREN", yytext);
                break;

            case RPAREN:
                printToken ("RPAREN", yytext);
                break;

            case LBRACE:
                printToken ("LBRACE", yytext);
                break;

            case RBRACE:
                printToken ("RBRACE", yytext);
                break;

            case ASSIGN:
                printToken ("ASSIGN", yytext);
                break;

            case RELOP:
                printToken ("RELOP", yytext);
                break;

            case BINOP:
                printToken ("BINOP", yytext);
                break;

            case COMMENT:
                printToken ("COMMENT", yytext);
                break;

            case ID:
                printToken ("ID", yytext);
                break;

            case NUM:
                printToken ("NUM", yytext);
                break;

            case NUM_B:
                printToken ("NUM_B", yytext);
                break;

            case STRING:
                printString ();
                break;

            /* Handling Errors */

        }
    }
    return 0;
}