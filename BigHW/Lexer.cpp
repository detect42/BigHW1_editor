//
// Created by Richard on 2023/6/23.
//

#include "Lexer.h"
#include <iostream>
extern bool OK;
Token::Token(int type, string s) {

    this->type = type;
    this->s = std::move(s);
}

Token::Token()=default;
char Lexer::Getnextchar(){
    if(nowpos==length) return EOF;
    nowpos++;
    return s[nowpos-1];
}
char Lexer::SkipBlank(char cc) {
    if (cc != ' ' && cc != '\t' && cc != '\n') {
        return cc;
    }
    char c = Getnextchar();
    while (c == ' ' || c == '\t' || c == '\n') {
        c = Getnextchar();
    }
    return c;
}

void Lexer::print(const Token& token) {
    if (token.type == Integer) {
        cout << "integer " << token.s << endl;
    } else if (token.type == Operator) {
        cout << token.s << endl;
    } else {
        cout << "identifier " << token.s << endl;
    }
}



Token Lexer::getToken(char cc) {
    Token ans;
    if (cc == EOF) {
        return Token{GG,""};
    }
    char fi = SkipBlank(cc);
    if (fi == EOF) {
        return Token(GG,"");
    }
    if (fi == '+' || fi == '-' || fi == '*' || fi == '/' || fi == '='||fi=='('||fi==')'||fi=='?'||fi==':'||fi=='<'||fi=='>') {
        ans = Token(Operator, string(1, fi));
        las = Getnextchar();
        if(fi=='='&&las=='='){
            ans.s="==";
            las=Getnextchar();
        }
    } else if (isdigit(fi)) {
        string s;
        s += fi;
        char c = Getnextchar();
        while (isdigit(c)) {
            s += c;
            c = Getnextchar();
        }
        las = c;
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')) OK=false;
        ans = Token(Integer, s);
    } else {
        string s;
        s += fi;
        char c = Getnextchar();
        while (isdigit(c) || isalpha(c)) {
            s += c;
            c = Getnextchar();
        }
        las = c;
        ans = Token(Identifier, s);
    }

    return ans;
}

void Lexer::GetNextToken() {
    tmp = getToken(las);
}
Token Lexer::GetCurToken() const {
    return tmp;
}
