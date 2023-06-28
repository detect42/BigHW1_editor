//
// Created by Richard on 2023/6/23.
//

#include "Statement.h"
#include <iostream>

Variable Variable;
CommandManager commandManager;
extern bool OK;
map<string,int> Map;
expression* parseExpression(Lexer &lexer) {
    expression* exp1 =parseExpression1(lexer);
    Token tk = lexer.GetCurToken();
    if (tk.s == "==" || tk.s == "<" || tk.s == ">") {
        lexer.GetNextToken();
        expression* exp2 = parseExpression1(lexer);
        if(lexer.GetCurToken().s!="?"){
            cout<<"error for unknown operator"<<endl;
            OK=false;return exp1;
         //   exit(2);
        }
        lexer.GetNextToken();//read the next of ?
        expression* exp3 = parseExpression1(lexer);
        if(lexer.GetCurToken().s!=":"){
            cout<<"error for unknown operator"<<endl;
            OK=false;return exp1;
           // exit(2);
        }
        lexer.GetNextToken();//read the next of :
        expression* exp4 = parseExpression1(lexer);
        expression* CMPexpression=new Binaryexpression(exp1,exp2,tk.s);
        exp1=new Ternaryexpression(CMPexpression,exp3,exp4,"?",":");
        return exp1;
    }
    else return exp1;
}
expression* parseExpression1(Lexer &lexer) {
    expression* expr = parseExpression2(lexer);
    Token tk = lexer.GetCurToken();
    while (tk.s == "+" || tk.s == "-") {
        lexer.GetNextToken();
        expression* expr2 = parseExpression2(lexer);
        expr=new Binaryexpression(expr,expr2,tk.s);
        tk = lexer.GetCurToken();
    }
    return expr;
}
expression* parseExpression2(Lexer &lexer) {
    expression* expr = parseExpression3(lexer);
    Token tk = lexer.GetCurToken();
    while (tk.s == "*" || tk.s == "/") {
        lexer.GetNextToken();
        expression* expr3 = parseExpression3(lexer);
        expr=new Binaryexpression(expr,expr3,tk.s);
        tk = lexer.GetCurToken();
    }
    return expr;
}

expression* parseExpression3(Lexer &lexer) {
    Token tk = lexer.GetCurToken();
    if (tk.s == "-") {
        lexer.GetNextToken();
        expression* expr = parseExpression4(lexer);
        expr =new UnaryExpression(expr, "-");
        return expr;
    } else {
        return parseExpression4(lexer);
    }
}

expression* parseExpression4(Lexer &lexer) {
    Token tk = lexer.GetCurToken();
    if (tk.type == Integer) {
        expression* expr;
        expr=new Intexpression(stoi(tk.s));
        lexer.GetNextToken();
        return expr;
    } else if (tk.type == Identifier) {
        expression* expr;
        expr=new Identifierexpression(tk.s);
        lexer.GetNextToken();
        return expr;
    } else if (tk.s == "(") {
        lexer.GetNextToken();
        expression* expr = parseExpression(lexer);
        Token tk2 = lexer.GetCurToken();
        if (tk2.s != ")") {
            cout << "error for none of )" << endl;
            OK=false;return expr;
         //   exit(3);
        }
        lexer.GetNextToken();
        return expr;
    } else {
        cout << "error for unknown type for exp4" << endl;
        OK=false;return new Intexpression(0);
      //  exit(4);
    }
}

bool isvaild(string content){

    Lexer lexer;lexer.nowpos=0;
    lexer.s=content;lexer.length=content.size();


    lexer.las = lexer.Getnextchar();

    OK=true;
    while (lexer.las != EOF) {
        lexer.GetNextToken();
        Token tk = lexer.GetCurToken();
        if(tk.type==GG) return 0;
        if (tk.s != "output") {
            lexer.GetNextToken();
            Token tk2 = lexer.GetCurToken();
            if (tk2.s == "=") {
                return Assignment(tk.s).isvaild(lexer);
            } else {
                cout << "error for unknown statement" << endl;
                return true;
            }
        } else {
            return Output().isvaild(lexer);
        }

    }

}
void Execute(string content){
    Lexer lexer;lexer.nowpos=0;
    lexer.s=content;lexer.length=content.size();
    lexer.las = lexer.Getnextchar();

    while (lexer.las != EOF) {
        lexer.GetNextToken();
        Token tk = lexer.GetCurToken();
        if(tk.type==GG) return;
        if (tk.s != "output") {
            lexer.GetNextToken();
            Token tk2 = lexer.GetCurToken();
            if (tk2.s == "=") {
                Assignment(tk.s).execute(lexer);
            } else {
                cout << "error for unknown statement" << endl;
                return;
            }
        } else {
            Output().execute(lexer);
        }

    }
    return;
}

//----------------------------------------statement--------------------------------------------
Assignment ::Assignment(string s) {
    name = std::move(s);
}
void Assignment::execute(Lexer &lexer) {
    lexer.GetNextToken();
    expression *exp = parseExpression(lexer);
    if(OK==false) return;
    Map[name] = exp->evaluate();
    commandManager.executeCommand(new VariableCommand(Variable, name, Map[name]));
    delete exp;
}
bool Assignment::isvaild(Lexer &lexer) {
    lexer.GetNextToken();
    expression *exp = parseExpression(lexer);
    if(OK==false) return true;
    Map[name] = exp->evaluate();
    delete exp;
    return false;
}
void Output::execute(Lexer &lexer) {
    lexer.GetNextToken();
    expression *exp = parseExpression(lexer);
    if(OK==false){
        delete exp;return;
    }
    cout << "the ansser is "<<exp->evaluate() << endl;
    delete exp;
}
bool Output::isvaild(Lexer &lexer) {
    lexer.GetNextToken();
    expression *exp = parseExpression(lexer);
    cout << "the asnser is "<<exp->evaluate() << endl;///////////
    delete exp;
    return !OK;
}
//x=x+2
//output x
