#ifndef MESH_H
#define MESH_H
/*

#include "vec.h"
#include "ogldev_texture.h"
*/

#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

class Mesh
{
  public:

    Mesh();
    ~Mesh();

    void carregarArquivo(string nomeArquivo);
    void jogaParaListaV(float a, float b, float c);
    void jogaParaListaVT(float a, float b);
    void jogaParaListaVN(float a, float b, float c);
    void jogaParaListaF(string a, string b, string c);
    /*
    vector<Vertex> getVertex();
    vector<unsigned int> getIndice();

  private:

    double encontrarDeltaX();
    double encontrarDeltaY();
    double encontrarDeltaZ();

    double deltaX, deltaY, deltaZ, xMin, yMin, zMin;
    int qtdPontos, qtdArestas, qtdTextura;
    vector<Vertex> vertex;
    vector<unsigned int> indice;
    
    string fileMtl;
    vector<Material> material;
    */
};

#endif

