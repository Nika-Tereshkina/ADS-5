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
  std::string r, r1;
  TStack<char, 100>stack1;
  for (auto& c : inf) {
    int p = GetPriority(c);
    if (p == -1) {
      r = r + с + ' ';
    } else {
      char element = stack1.get();
      if (p == 0 || GetPriority(elem) < p || stack1.isEmpty()) {
        stack1.push(c);
      } else {
        if (c == ')') {
          while (GetPriority(element) >= p) {
            r = r + element + ' ';
            stack1.pop();
            element = stack1.get();
          }
          stack1.pop();
        } else {
          while (GetPriority(element) >= p) {
            r = r + element + ' ';
            stack1.pop();
            element = stack1.get();
          }
          stack1.push(c);
        }
      }
    }
  }
  while (!stack1.isEmpty()) {
    r = r + stack1.get() + ' ';
    stack1.pop();
  }
  for (int i = 0; i < r.size() - 1; i++)
    r1 += r[i];
  return r1;
}

int schetchik(const int& p, const int& q, const int& c) {
  switch (c) {
    case '+':
      return p + q;
    case '-':
      return p - q;
    case '/':
      return p / q;
    case '*':
      return p * q;
    default:
      return 0;
  }
}

int eval(std::string pref) {
  TStack<int, 100> stack1;
  std::string r = "";
  for (int i = 0; i < pref.size(); i++) {
    char element = pref[i];
    if (GetPriority(element) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        r += pref[i];
        continue;
      } else {
        r += pref[i];
        stack1.push(atoi(r.c_str()));
        r = "";
      }
    } else {
      int q = stack1.get();
      stack1.pop();
      int p = stack1.get();
      stack1.pop();
      stack1.push(schetchik(p, q, element));
    }
  }
  return stack1.get();
}
