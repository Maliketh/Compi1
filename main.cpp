#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>

#define MAX_STRING_LEN 1024


/* =========  Helper function - in the feuture maybe move to a new file   =========*/

/*
Reminder:
   yylineno is a global variable provided by Flex  that keeps track of the current line number being processed in the input stream.
   yyleng represents the number of characters in the current match, excluding the null terminator.
   yytext is a global variable provided by Flex that contains the text of the current token that was matched by the lexer.
   It points to a null-terminated string representing the input that corresponds to the pattern in your Flex rules
*/

void printString()
{
    std::string output = "";

    /* Skip the first and last index to avoid  "" */
    for (int i = 1; i < yyleng - 1; i++)
    {
        if (output.size() > MAX_STRING_LEN)
        {
            //scream something
        }
        if (yytext[i] == '\\')
        {
            char cur_char = yytext[++i];

            switch (cur_char)
            {
            case 'n':
                output.push_back('\n');
                break;

            case 'r':
                output.push_back('\r');
                break;

            case 't':
                output.push_back('\t');
                break;

            case '\\':
                output.push_back('\\');
                break;

            case '"':
                output.push_back('\"');
                break;

            case 'x':
                std::string ascii_val = "";
                ascii_val.append(&yytext[++i], 2);
                int hexValue = std::stoi(ascii_val, nullptr, 16);
                if (hexValue < 0 || hexValue > 255)
                {
                    output::errorUndefinedEscape(ascii_val.c_str());
                    exit(0);
                }
                char val = static_cast<char> (hexValue);
                output.push_back(val);
                i++;
                break;

           // default:
                //error - NOT SURE WHICH ONE PROBABLY DEBUG,
               // break;


            }

        }
        else
        {
            output.push_back(yytext[i]);
        }
    }

    output::printToken(yylineno, STRING, output.c_str());
}

void char_error()
{
    int i = 0;
    while (yytext[i])
    {
        if (!((int(yytext[i]) >= int(0x20) &&
               int(yytext[i]) <= int(0x7E) && 
               int(yytext[i]) != int(0x7f))))
        {
            output::errorUnknownChar(yytext[i]);
            exit(0);
        }
        i++;
    }
}


/* ==========================  End of helper functions   ==========================*/



int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex())))
    {
        switch (token)
        {
        case VOID:
            output::printToken(yylineno, VOID, yytext);
            break;

        case INT:
            output::printToken(yylineno, INT, yytext);
            break;

        case BYTE:
            output::printToken(yylineno, BYTE, yytext);
            break;

        case BOOL:
            output::printToken(yylineno, BOOL, yytext);
            break;

        case AND:
            output::printToken(yylineno, AND, yytext);
            break;

        case OR:
            output::printToken(yylineno, OR, yytext);
            break;

        case NOT:
            output::printToken(yylineno, NOT, yytext);
            break;

        case TRUE:
            output::printToken(yylineno, TRUE, yytext);
            break;

        case FALSE:
            output::printToken(yylineno, FALSE, yytext);
            break;

        case RETURN:
            output::printToken(yylineno, RETURN, yytext);
            break;

        case IF:
            output::printToken(yylineno, IF, yytext);
            break;

        case ELSE:
            output::printToken(yylineno, ELSE, yytext);
            break;

        case WHILE:
            output::printToken(yylineno, WHILE, yytext);
            break;

        case BREAK:
            output::printToken(yylineno, BREAK, yytext);
            break;


        case CONTINUE:
            output::printToken(yylineno, CONTINUE, yytext);
            break;

        case SC:
            output::printToken(yylineno, SC, yytext);
            break;

        case COMMA:
            output::printToken(yylineno, COMMA, yytext);
            break;

        case LPAREN:
            output::printToken(yylineno, LPAREN, yytext);
            break;

        case RPAREN:
            output::printToken(yylineno, RPAREN, yytext);
            break;

        case LBRACE:
            output::printToken(yylineno, LBRACE, yytext);
            break;

        case RBRACE:
            output::printToken(yylineno, RBRACE, yytext);
            break;

        case ASSIGN:
            output::printToken(yylineno, ASSIGN, yytext);
            break;

        case RELOP:
            output::printToken(yylineno, RELOP, yytext);
            break;

        case BINOP:
            output::printToken(yylineno, BINOP, yytext);
            break;

        case COMMENT:
            output::printToken(yylineno, COMMENT, yytext);
            break;

        case ID:
            output::printToken(yylineno, ID, yytext);
            break;

        case NUM:
            output::printToken(yylineno, NUM, yytext);
            break;

        case NUM_B:
            output::printToken(yylineno, NUM_B, yytext);
            break;

        case STRING:
            printString();
            break;

            /* Handling Errors */
        case ERR_UNCLOSED_STR:
            output::errorUnclosedString();
            exit(0);
            break;

        case ERR_GENERAL:
            char_error(); //HOW TO GET THE CHAR??
            break;

        case ERR_UNDEFINED_ESC: //maybe handle in printString?
            printString();
            break;

        }
    }
    return 0;
}