// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
bool Oper(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
int Prior(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}
std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string pst;
    int len = inf.length();
    for (int i = 0; i < len; i++) {
        char c = inf[i];
        if (isspace(c)) {
            continue;
            } else if (isdigit(c)) {
            pst += c;
            pst += ' ';
            } else if (Oper(c)) {
            int pr = Prior(c);
            while (!stack.isEmpty() && stack.get() != '(' && Prior(stack.get()) >= pr) {
                pst += stack.pop();
                pst += ' ';
            }
            stack.push(c);
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                pst += stack.pop();
                pst += ' ';
            }
            stack.pop();
        }
    }
    while (!stack.isEmpty()) {
        pst += stack.pop();
        pst += ' ';
    }
    if (!pst.empty()) {
        pst.pop_back(); 
    }
    return pst;
}
int eval(std::string pref) {
    TStack<int, 100> stack;
    int len = pref.length();
    for (int i = 0; i < len; i += 2) {
        char c = pref[i];
        if (isdigit(c)) {
            int num = c - '0';
            stack.push(num);
            } else if (Oper(c)) {
            int op2 = stack.pop();
            int op1 = stack.pop();
            int result;
            switch (c) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }
            stack.push(result);
        }
    }
    return stack.pop();
}
