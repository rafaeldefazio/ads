#include "Expression.h"

using namespace std;

// pre: nenhuma
// pos: Dada expressao infixa expression, converte-a na notacao posfixa expression encontra seu valor
Expression::Expression(string expression) {
    setInfix(expression);
}

// pre: nenhuma
// pos: Dada expressao infixa s, converte-a na notacao posfixa e encontra seu valor
void Expression::setInfix(string expression) {
    infix = expression;
    infixToPostfix();
    evalPostfix();
}

// pre: objeto criado
// pos: retorna a expressao na notacao infixa
string Expression::getInfix() {
    return infix;
}

// pre: objeto criado
// pos: retorna a expressao na notacao posfixa (RPN)
string Expression::getPostfix() {
    return postfix;
}

// pre: objeto criado
// pos: retorna o valor da expressao na notacao posfixa (RPN)
int Expression::getValue() {
    return value;
}


// pre: seja um char valido
// pos: retorna peso do char
int Expression::precedence(char opr) {

    switch (opr) {

    case '^':
        return 3;
        break;

    case '*':
    case '/':
    case '%':
        return 2;
        break;

    case '+':
    case '-':
        return 1;
        break;

    default:
        return 0;
        break;

    }

}


// pre: seja dois char validos
// pos: retorna resultado do calculo em questao
int Expression::operation(char opr, int a, int b) {

    switch (opr) {

    case '^':
        return pow(a, b);
        break;

    case '*':
        return a * b;
        break;

    case '/':
        return a / b;
        break;

    case '%':
        return a % b;
        break;

    case '+':
        return a + b;
        break;

    case '-':
        return a - b;
        break;

    default:
        return 0;
        break;

    }

}

// pre: infix contem uma expressao aritmetica valida, contendo operadores e digitos na notacao infixa, nao utilizando operacoes /0 e %0.
// pos: postfix contem a mesma expressao dada por infix, convertida na notacao pos-fixada (RPN)
void Expression::infixToPostfix() {

    // variavel contando postfix
    postfix = "";

    Stack < char > opr; // um pilha de caracteres
    char t; // topo da pilha

    // Percorre a expressao inserida, caractere a caractere
    for (unsigned int i = 0; i < infix.size(); i++) {

        // caso a pilha ja esteja cheia no meio da expressao, nao eh possivel concluir
        if (opr.full())
            abort();

        // considerando que usuario inseriu inteiro de 0 a 9 para cada operando, adiciona digito à string postfix
        if (isdigit(infix[i]))
            postfix += infix[i];

        // caso for, parênteses esquerdo, adicionar à pilha
        else if (infix[i] == '(')
            opr.push(infix[i]);

        // se operador for conhecido, adiciona-lo na pilha...
        else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '+' || infix[i] == '-') {

            // enquanto a pilha não estiver vazia...
            while (!opr.empty()) {

                opr.getTop(t);

                // se encontrar '(' ou preferencia do operador t for menor que Ui)...
                if (t == '(' || (precedence(t) < precedence(infix[i])))
                    break; // sair do loop

                // senao, transferir elementos da pilha para postfix
                opr.pop(t);
                postfix += t;

            }

            // adicinar Ui na pilha
            opr.push(infix[i]);

            // caso encontre ')'
        } else if (infix[i] == ')') {

            // transferir elementos da pilha para postfix ate encontrar '(' e descartar '('.
            opr.pop(t);

            while (t != '(') {
                postfix += t;
                opr.pop(t);
            }

            // caso expressao for vazia, ignorar
        } else if (infix[i] == ' ') {}

        // caso expressao for invalida, abortar
        else {
            abort();
        }

    }

    // transfere simbolos da pilha para postfix
    while (!opr.empty()) {
        opr.pop(t);
        postfix += t;
    }

}

// pre: postfix contem a expressao na notacao posfixa
// pos: retorna o valor da expressao, utilzando Algoritmo 2
void Expression::evalPostfix() { // Implemente o Algoritmo 2 aqui
    

    value = 0; // valor calculado

    // para declarar uma pilha usando templates, associe o tipo de dado colocado na mesma 
    Stack < int > number; // um pilha de inteiros

    // percorre postfix caractere a caractere
    for (unsigned int i = 0; i < postfix.size(); i++) {

        // verifica Ui se é digit
        if (isdigit(postfix[i]))
            number.push(postfix[i] - '0'); // char para int, subtraindo '0' (48)
            // pilha nao vai ficar cheia, pois infix ja foi processado

        // caso Ui seja uma operacao...
        else if (postfix[i] == '^' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '+' || postfix[i] == '-') {

            int a, b;

            // remove dois elementos da pilha
            number.pop(b);
            number.pop(a);

            // faz operacao correspondente e insere resultado na pilha
            number.push(operation(postfix[i], a, b));
        }

    }

    // caso postfix nao tenha caracteres (string vazia) ou apenas espacos, retorne zero
    if (postfix != "")
        number.getTop(value);

}