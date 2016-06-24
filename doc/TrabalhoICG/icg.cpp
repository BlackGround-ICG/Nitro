
//#include <SDL2/SDL.h>
//#include <GL/glew.h>
//#include <GL/glext.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "ogldev_util.h"
#include "math_3d.h"
#include "vec.h"
#include "mesh.h"

struct objeto {
    //lista vetor de pontos de vertex
    //vetor de normal
    //vetor de textura
    //vetor das listas de tringulos (faces)
    //ponteiro para imagem de textura mtl

}
/*
 Laço principal */
void Mesh::carregarArquivo(string nomeArquivo)
{
  ifstream arquivo(nomeArquivo.c_str()); //retorna o char ponteiro, recebe c*

  if(!arquivo.is_open())
  {
    cout << "Não foi possível abrir o aquivo!!!" << endl;
    exit(-1);
  }

  string tipo;
  getline(arquivo, tipo);
  
  if(tipo.find("OFF") == string::npos)
  {
    cout << "Tipo de arquivo invalido!!!" << endl;
    exit(-1);
  }

  string line;
  getline(arquivo, line);

  stringstream ss (line);
  ss >> this->qtdPontos >> this->qtdArestas >> this->qtdTextura;

  for(int i=0; i<this->qtdPontos; i++)
  {
    string linha;

    getline(arquivo, linha);
    stringstream buffer(linha);

    float x, y, z;
    int r, g, b, alpha;

    if(tipo.find("COFF") != string::npos)
    {
      buffer >> x >> y >> z >> r >> g >> b >> alpha;
    }
    else if(tipo.find("OFF") != string::npos)
    {
      buffer >> x >> y >> z;
    }

    Vertex tempVertex = Vertex(x, y, z, 1.0, 0.0, 0.0, 1.0);
    this->vertex.push_back(tempVertex);

  }

  for(int j=0; j<this->qtdArestas; j++)
  {
    string linha;

    getline(arquivo, linha);
    stringstream buffer(linha);

    unsigned int valor, indice1, indice2, indice3;

    buffer >> valor >> indice1 >> indice2 >> indice3;
    this->indice.push_back(indice1);
    this->indice.push_back(indice2);
    this->indice.push_back(indice3);
  } 

  arquivo.close();

  this->deltaX = this->encontrarDeltaX();
  this->deltaY = this->encontrarDeltaY();
  this->deltaZ = this->encontrarDeltaZ();
}
int
main(int argc, char* argv[])
{
    char arquivo[100];
    cout << "Nome do Arquivo:\n";
    cin >> arquivo;
    Mesh::carregarArquivo(arquivo);
  

    return 0;
}