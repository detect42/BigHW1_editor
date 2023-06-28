//
// Created by Richard on 2023/6/23.
//

#ifndef BIGHW_STATEMENT_H
#define BIGHW_STATEMENT_H
#include "Expression.h"

expression *parseExpression(Lexer &lexer);
expression *parseExpression1(Lexer &lexer);
expression *parseExpression2(Lexer &lexer);
expression *parseExpression3(Lexer &lexer);
expression *parseExpression4(Lexer &lexer);
bool isvaild(string content);
void Execute(string content);
class Statement{
public:
    virtual void execute(Lexer &lexer)=0;
    virtual bool isvaild(Lexer &lexer)=0;
};
class Assignment : public Statement {
public:
    string name;
    explicit Assignment(string s);
    virtual void execute(Lexer &lexer) override;
    virtual bool isvaild(Lexer &lexer) override;
};
class Output : public Statement {
public:
    virtual void execute(Lexer &lexer) override;
    virtual bool isvaild(Lexer &lexer) override;
};
#endif //BIGHW_STATEMENT_H
