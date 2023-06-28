#include "Expression.h"
#include <iostream>
extern map<string,int> Map;
extern bool OK;

Intexpression::Intexpression(int a) {
    val = a;
}
int Intexpression::evaluate() {
    return val;
}

Identifierexpression::Identifierexpression(string s){
    str=std::move(s);
}
int Identifierexpression::evaluate() {
    return Map[str];
}


UnaryExpression::UnaryExpression(expression *a,string s):exp(a),op(std::move(s)){}
UnaryExpression::~UnaryExpression() {
    delete exp;
}
int UnaryExpression::evaluate() {
    if(op=="-"){
        return -exp->evaluate();
    }
    else if(op=="!"){
        if(exp->evaluate()==True){
            return False;
        }
        else return True;
    }
    else{
        cout<<"error for unknown unary operator"<<endl;
        OK=false;return 0;
        exit(2);
    }
}

Binaryexpression::Binaryexpression(expression *a,expression *b,string s):expL(a),expR(b),op(std::move(s)){}
Binaryexpression::~Binaryexpression()  {
    delete expL;
    delete expR;
}
int Binaryexpression::evaluate() {
    if(op=="+"){
        return expL->evaluate()+expR->evaluate();
    }
    else if(op=="-"){
        return expL->evaluate()-expR->evaluate();
    }
    else if(op=="*"){
        return expL->evaluate()*expR->evaluate();
    }
    else if(op=="/"){
        return expL->evaluate()/expR->evaluate();
    }
    else if(op=="=="){
        if(expL->evaluate()==expR->evaluate()){
            return True;
        }
        else return False;
    }
    else if(op=="<"){
        if(expL->evaluate()<expR->evaluate()){
            return True;
        }
        else return False;
    }
    else if(op==">"){
        if(expL->evaluate()>expR->evaluate()){
            return True;
        }
        else return False;
    }
    else{
        cout<<"error for unknown binary operator"<<endl;
        OK=false;return 0;
        exit(1);
    }
}

Ternaryexpression::Ternaryexpression(expression *a,expression *b,expression *c,string s1,string s2):exp1(a),exp2(b),exp3(c),op1(std::move(s1)),op2(std::move(s2)){}
Ternaryexpression::~Ternaryexpression()  {
        delete exp1;
        delete exp2;
        delete exp3;
    }
int Ternaryexpression:: evaluate(){
    if(op1=="?"&&op2==":"){
        if(exp1->evaluate()==True){
            return exp2->evaluate();
        }
        else return exp3->evaluate();
    }
    else{
        cout<<"error for unknown ternary operator"<<endl;
        OK=false;return 0;
        exit(1);
    }
}
