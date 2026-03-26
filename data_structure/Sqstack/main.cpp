#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MaxSize 100  // 操作符栈容量，10 太小，建议调大

typedef struct {
    char data[MaxSize];
    int top;               // 必须是 int
} SqStack;

void InitStack(SqStack &S) {
    S.top = -1;
}

bool StackEmpty(SqStack &S) {
    return S.top == -1;
}

bool Push(SqStack &S, char x) {
    if (S.top == MaxSize - 1) return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, char &x) {
    if (StackEmpty(S)) return false;
    x = S.data[S.top--];
    return true;
}

bool GetTop(SqStack &S, char &x) {
    if (StackEmpty(S)) return false;
    x = S.data[S.top];
    return true;
}

// ====== Infix -> Postfix helpers ======

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperand(char c) {
    // 考研常见：数字/字母都当操作数（单字符）
    return isNumber(c) || isLetter(c);
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

bool isRightAssociative(char op) {
    // 通常只有幂运算右结合
    return op == '^';
}

// 只支持 () 作为括号（中缀表达式标准转换用这个最常见）
bool isLeftParen(char c)  { return c == '('; }
bool isRightParen(char c) { return c == ')'; }

// 成功返回 true；失败返回 false（非法字符/括号不匹配/输出溢出/栈溢出）
bool InfixToPostfix(const char *infix, char *postfix, int postfix_cap) {
    if (!infix || !postfix || postfix_cap <= 0) return false;

    SqStack S;
    InitStack(S);

    int j = 0; // postfix 写入位置

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // 跳过空格
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') continue;

        if (isOperand(c)) {
            // 输出操作数
            if (j >= postfix_cap - 1) return false;
            postfix[j++] = c;
        } else if (isLeftParen(c)) {
            if (!Push(S, c)) return false; // 栈满
        } else if (isRightParen(c)) {
            // 弹到遇到 '('
            char topc;
            bool found_left = false;
            while (Pop(S, topc)) {
                if (isLeftParen(topc)) {
                    found_left = true;
                    break;
                }
                if (j >= postfix_cap - 1) return false;
                postfix[j++] = topc;
            }
            if (!found_left) return false; // 没找到 '('，括号不匹配
        } else if (isOperator(c)) {
            // 处理优先级/结合性：
            // 左结合：遇到同优先级也要弹
            // 右结合：遇到同优先级不弹
            char topc;
            while (GetTop(S, topc) && isOperator(topc)) {
                int p_top = precedence(topc);
                int p_cur = precedence(c);

                bool should_pop =
                    (p_top > p_cur) ||
                    (p_top == p_cur && !isRightAssociative(c));

                if (!should_pop) break;

                Pop(S, topc);
                if (j >= postfix_cap - 1) return false;
                postfix[j++] = topc;
            }
            if (!Push(S, c)) return false; // 栈满
        } else {
            // 非法字符
            return false;
        }
    }

    // 把栈里剩余操作符全部弹出
    char topc;
    while (Pop(S, topc)) {
        if (isLeftParen(topc)) return false; // 还有 '('，括号不匹配
        if (j >= postfix_cap - 1) return false;
        postfix[j++] = topc;
    }

    postfix[j] = '\0';
    return true;
}

int main() {
    const char *infix = "a+b*(c-d)^e";
    char postfix[256];

    if (InfixToPostfix(infix, postfix, (int)sizeof(postfix))) {
        printf("infix:   %s\n", infix);
        printf("postfix: %s\n", postfix);
    } else {
        printf("convert failed\n");
    }
    return 0;
}