//
// Created by Richard on 2023/6/23.
//

#ifndef BIGHW_LEXER_H
#define BIGHW_LEXER_H
#include<string>
#include<QtDebug>
#include "command.h"
using namespace std;

#define True 1
#define False 0
enum type {
    Integer, Operator, Identifier, GG
};


class Token {
public:
    int type;
    string s;

    Token(int type, string s);

    Token();
};



class Lexer {

private:
    char SkipBlank(char cc);

public:
    void print(const Token& token);
    char Getnextchar();
    char las;
    int nowpos;
    string s;
    int length;

    Token getToken(char cc);


    Token tmp;
    void GetNextToken();
    Token GetCurToken() const;

};

#endif //BIGHW_LEXER_H
