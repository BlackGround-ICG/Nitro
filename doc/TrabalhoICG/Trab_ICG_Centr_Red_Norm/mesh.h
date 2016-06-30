#ifndef MESH_H
#define MESH_H

#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include <math.h>

using namespace std;

class Mesh
{
  public:

    Mesh();
    ~Mesh();
    typedef struct struct_lista Lista;
    void carregarArquivo(string nomeArquivo,Lista *listaCompleta);
    void jogaParaListaV(float a, float b, float c,Lista *listaCompleta);
    void jogaParaListaVT(float a, float b,Lista *listaCompleta);
    void jogaParaListaVN(double a, double b, double c,Lista *listaCompleta);
    void jogaParaListaF(string a, string b, string c,Lista *listaCompleta);
    void normalizaVetor(float a, float b, float c);
    void centralizaObj(Lista *listaCompleta);
    void redimensionaObj(Lista *listaCompleta);

};

#endif
