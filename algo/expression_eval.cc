#include <string>
#include <stack>
#include <cstdlib>
#include <cstdio>
using namespace std;

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

int precede(char a, char b) {
  if ((a == '(' && b == ')') ||(a == '#' && b == '#')) {
    return 0;
  }
  if (a == '(' || b == '(') {
    return -1;
  }
  if (a == ')' || b == ')') {
    return 1;
  }
  if (a == '#') {
    return -1;
  }
  if (b == '#') {
    return 1;
  }
  if (a == b) {
    return 1;
  }
  if ((a == '+' || a == '-') && (b == '*' || b == '/')) {
    return -1;
  }
  if ((a == '*' || a == '/') && (b == '+' || b == '-')) {
    return 1;
  }
  return 1;
}

int operate(int lhs, char c, int rhs) {
  switch (c) {
    case '+' : return lhs+rhs;
    case '-' : return lhs-rhs;
    case '*' : return lhs*rhs;
    case '/' : return lhs/rhs;
    default: return 0;
  }
}

/**
 * @param expression: a string
 * @return: an integer
 */
int evaluateExpression(string expression) {
  if (expression.empty()) {
    return 0;
  }

  stack<int> operands;
  stack<char> operators;
  operators.push('#');
  expression.push_back('#');

  const char *pc = expression.c_str();
  while (*pc != '#' || operators.top() != '#') {
    if (isDigit(*pc)) {
      operands.push(atoi(pc));
      while (isDigit(*pc)) ++pc;
    } else {
      switch (precede(operators.top(), *pc)) {
        case -1: // <
          operators.push(*pc++);
          break;
        case 0: // ==
          operators.pop();
          ++pc;
          break;
        case 1: // >
          int rhs = operands.top(); operands.pop();
          int lhs = operands.top(); operands.pop();
          operands.push(operate(lhs, operators.top(), rhs));
          operators.pop();
      }
    }
  }

  return operands.top();
}

int main() {
  string expr = "1+2+(3+4)+5*20-10/5*10/2+(2+2)*(3+8/(6-4))";
  printf("%s = %d\n", expr.c_str(), evaluateExpression(expr));
  return 0;
}
