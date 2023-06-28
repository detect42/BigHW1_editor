//
// Created by Richard on 2023/6/23.
//

#ifndef BIGHW_EXPRESSION_H
#define BIGHW_EXPRESSION_H
#include <map>
#include "Lexer.h"

class expression{
public:
    virtual int evaluate()=0;
    virtual ~expression()=default;
};

class Intexpression:public expression{
private:
    int val;
public:
    explicit Intexpression(int a);
    virtual int evaluate() override;
};

class Identifierexpression:public expression{
private:
    string str;
public:
    explicit Identifierexpression(string s);
    virtual int evaluate() override;
};

class UnaryExpression:public expression{
private:
    expression *exp;
    string op;
public:
    UnaryExpression(expression *a,string s);
    ~UnaryExpression() override ;
    virtual int evaluate() override;
};

class Binaryexpression:public expression{
private:
    expression *expL,*expR;
    string op;
public:
    Binaryexpression(expression *a,expression *b,string s);
    ~Binaryexpression() override;
    virtual int evaluate() override;
};

class Ternaryexpression:public expression{
private:
    expression *exp1,*exp2,*exp3;
    string op1,op2;
public:
    Ternaryexpression(expression *a,expression *b,expression *c,string s1,string s2);
    ~Ternaryexpression() override ;
    virtual int evaluate() override;

};

#endif //BIGHW_EXPRESSION_H
