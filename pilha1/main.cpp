#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

TipoCelula *Topo; // Variavel para o topo da pilha
int Contador;     // Contador de elementos na pilha

// Implementacoes das funcoes da pilha
void Pilha_Construtor() {
    Topo = NULL;
    Contador = 0;
}

void Pilha_Destrutor() {
    TipoCelula *Temp;
    while (Topo != NULL) {
        Temp = Topo;
        Topo = Topo->Prox;
        free(Temp);
    }
    Contador = 0;
}

bool Pilha_Vazia() {
    return Topo == NULL;
}

int Pilha_Tamanho() {
    return Contador;
}

bool Pilha_Empilhar(TipoDado Elemento) {
    TipoCelula *Nova = (TipoCelula *) malloc(sizeof(TipoCelula));
    if (Nova == NULL) {
        return false;
    }
    Nova->Item = Elemento;
    Nova->Prox = Topo;
    Topo = Nova;
    Contador++;
    return true;
}

bool Pilha_Desempilhar(TipoDado &Elemento) {
    if (!Pilha_Vazia()) {
        TipoCelula *Temp = Topo;
        Topo = Topo->Prox;
        Elemento = Temp->Item;
        free(Temp);
        Contador--;
        return true;
    }
    return false;
}

bool Pilha_Topo(TipoDado &Elemento) {
    if (!Pilha_Vazia()) {
        Elemento = Topo->Item;
        return true;
    }
    return false;
}

// Funcao para validar a expressao
bool isValidExpression(const std::string& expression) {
    Pilha_Construtor();
    TipoDado element;

    for (char ch : expression) {
        if (ch == '(' || ch == '[') {
            Pilha_Empilhar(ch);
        } else if (ch == ')' || ch == ']') {
            if (Pilha_Vazia() ||
                (ch == ')' && !Pilha_Topo(element) && element != '(') ||
                (ch == ']' && !Pilha_Topo(element) && element != '[')) {
                Pilha_Destrutor();
                return false;
            }
            Pilha_Desempilhar(element);
        }
    }
    bool valid = Pilha_Vazia();
    Pilha_Destrutor();
    return valid;
}

int main() {
    std::string expression;
    std::cout << "Digite uma expressao matematica: ";
    std::getline(std::cin, expression);

    if (isValidExpression(expression)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "Errado" << std::endl;
    }

    return 0;
}
