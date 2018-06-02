#ifndef GUI_H
#define GUI_H

typedef struct Guitarra guitar;

struct Guitarra{
    int id;
    char nome[50];
    int estado;
    int valor;
    int pdia;
};



#endif