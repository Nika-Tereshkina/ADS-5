// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int GetPriority(char c) {
switch (c) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    default:
        return -1;
    }
}
std::string infx2pstfx(std::string inf) {
std::string postfix, temp;
TStack<char, 100> operators;
for (auto& ch : inf) {
    int priority = GetPriority(ch);
    if (priority == -1) {
        postfix += ch;
        postfix += ' ';
    } else {
        char top = operators.get();
        if (priority == 0 || GetPriority(top) < priority || operators.isEmpty()) {
            operators.push(ch);
        } else {
            if (ch == ')') {
                while (GetPriority(top) >= priority) {
                    postfix += top;
                    postfix += ' ';
                    operators.pop();
                    top = operators.get();
                }
                operators.pop();
                } else {
                    while (GetPriority(top) >= priority) {
                        postfix += top;
                        postfix += ' ';
                        operators.pop();
                        top = operators.get();
                     }
                     operators.push(ch);
                }
            }
       }
    }
    while (!operators.isEmpty()) {
        postfix += operators.get();
        postfix += ' ';
        operators.pop();
    }
    return postfix;
}
int calculate(const int& op1, const int& op2, const char& oper) {
switch (oper) {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '/':
        return op1 / op2;
    case '*':
        return op1 * op2;
    default:
        return 0;
    }
}
int eval(std::string pref) {
TStack<int, 100> operands;
std::string temp = "";
for (int i = 0; i < pref.size(); i++) {
    char ch = pref[i];
    if (GetPriority(ch) == -1) {
        if (pref[i] == ' ') {
            continue;
        } else if (std::isdigit(pref[i+1])) {
            temp += pref[i];
            continue;
        } else {
            temp += pref[i];
            operands.push(atoi(temp.c_str()));
            temp = "";
        }
    } else {
        int op2 = operands.get();
        operands.pop();
        int op1 = operands.get();
        operands.pop();
        operands.push(calculate(op1, op2, ch));
        }
    }
    return operands.get();
}
