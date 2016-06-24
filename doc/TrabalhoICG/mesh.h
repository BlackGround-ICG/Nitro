#ifndef MESH_H
#define MESH_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "vec.h"
//#include "ogldev_texture.h"

using namespace std;

class Mesh
{
  public:

    Mesh();
    ~Mesh();

    void carregarArquivo(string nomeArquivo);
    void redimensionar();
    void normalizar();
    void transladar();

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
};

#endif

