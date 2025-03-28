#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack_double;

typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

void initDoubleStack(Stack_double *s) {
    s->top = -1;
}

void initCharStack(CharStack *s) {
    s->top = -1;
}

int isEmptyDoubleStack(Stack_double *s) {
    return s->top == -1;
}

int isEmptyCharStack(CharStack *s) {
    return s->top == -1;
}

int isFullDoubleStack(Stack_double *s) {
    return s->top == MAX_SIZE - 1;
}

int isFullCharStack(CharStack *s) {
    return s->top == MAX_SIZE - 1;
}

void pushDouble(Stack_double *s, double value) {
    if (!isFullDoubleStack(s)) {
        s->data[++s->top] = value;
    }
}

void pushChar(CharStack *s, char value) {
    if (!isFullCharStack(s)) {
        s->data[++s->top] = value;
    }
}

double popDouble(Stack_double *s) {
    if (!isEmptyDoubleStack(s)) {
        return s->data[s->top--];
    }
    return NAN;
}

char popChar(CharStack *s) {
    if (!isEmptyCharStack(s)) {
        return s->data[s->top--];
    }
    return '\0';
}

double peekDouble(Stack_double *s) {
    return isEmptyDoubleStack(s) ? NAN : s->data[s->top];
}

char peekChar(CharStack *s) {
    return isEmptyCharStack(s) ? '\0' : s->data[s->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : NAN;
    }
    return NAN;
}

double evaluateExpression(const char *expr, int *errorPos) {
    Stack_double values;
    CharStack ops;
    initDoubleStack(&values);
    initCharStack(&ops);

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i]) || expr[i] == '.') {
            char numBuffer[32];
            int j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                numBuffer[j++] = expr[i++];
            }
            numBuffer[j] = '\0';
            pushDouble(&values, atof(numBuffer));
            i--;
        } else if (expr[i] == '(') {
            pushChar(&ops, expr[i]);
        } else if (expr[i] == ')') {
            while (!isEmptyCharStack(&ops) && peekChar(&ops) != '(') {
                double b = popDouble(&values);
                double a = popDouble(&values);
                char op = popChar(&ops);
                pushDouble(&values, applyOp(a, b, op));
            }
            if (!isEmptyCharStack(&ops)) popChar(&ops);
            else { *errorPos = i; return NAN; }
        } else if (strchr("+-*/", expr[i])) {
            while (!isEmptyCharStack(&ops) && precedence(peekChar(&ops)) >= precedence(expr[i])) {
                double b = popDouble(&values);
                double a = popDouble(&values);
                char op = popChar(&ops);
                pushDouble(&values, applyOp(a, b, op));
            }
            pushChar(&ops, expr[i]);
        } else {
            *errorPos = i;
            return NAN;
        }
    }

    while (!isEmptyCharStack(&ops)) {
        double b = popDouble(&values);
        double a = popDouble(&values);
        char op = popChar(&ops);
        pushDouble(&values, applyOp(a, b, op));
    }

    return popDouble(&values);
}

void processFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) return;

    char line[256];
    while (fgets(line, sizeof(line), in)) {
        int errorPos = -1;
        double result = evaluateExpression(line, &errorPos);
        if (isnan(result)) {
            fprintf(out, "Ошибка в позиции %d\n", errorPos);
        } else {
            fprintf(out, "%lf\n", result);
        }
    }

    fclose(in);
    fclose(out);
}
