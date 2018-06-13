/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   guitarra.h
 * Author: nunob
 *
 * Created on 7 de Junho de 2018, 0:56
 */

#ifndef GUITARRA_H
#define GUITARRA_H

typedef struct Guitarra guitar;

struct Guitarra {
    int id;
    char nome[50];
    int estado;
    int valor;
    int pdia;
};


#endif /* GUITARRA_H */

