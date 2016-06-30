#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>

using namespace std;
//using namespace ijengine;


typedef struct struct_lista {
  list<float> listaV;
  list<float> listaVT;
  list<double> listaVN;
  list<string> listaF;
  float xMin, xMax, yMin, yMax, zMax, zMin;
  float deltaX, deltaY, deltaZ;
} Lista;

void jogaParaListaV(float a, float b, float c, Lista *listaCompleta){
  listaCompleta->listaV.push_back(a);
  listaCompleta->listaV.push_back(b);
  listaCompleta->listaV.push_back(c);
}

void jogaParaListaVT(float a, float b,Lista *listaCompleta){
  listaCompleta->listaVT.push_back(a);
  listaCompleta->listaVT.push_back(b);
}

void normalizaVetor(double *a, double *b, double *c){
  double norma = 0;
  norma = sqrt(pow(*a,2) + pow(*b,2) + pow(*c,2));
  *a = *a/norma*1.0;
  *c = *b/norma*1.0;
  *c = *c/norma*1.0;
  //printf("Normalizados: A -> %.5lf B -> %.5lf C -> %.5lf\n",*a,*b,*c);
}

void redimensionaObj(Lista *listaCompleta){
  //ver maior delta
  float maiorDelta = -100000;
  if(listaCompleta->deltaX > maiorDelta) maiorDelta = listaCompleta->deltaX;
  if(listaCompleta->deltaY > maiorDelta) maiorDelta = listaCompleta->deltaY;
  if(listaCompleta->deltaZ > maiorDelta) maiorDelta = listaCompleta->deltaZ;

  for (list<float>::iterator it = listaCompleta->listaV.begin(); it != listaCompleta->listaV.end(); it++){
    *it = *it/maiorDelta*1.0;
  }
  
  /*
// Tamanho máximo em uma das axis 
  //(deta_x, delta_y, ou delta_z tem ser maximo 1)
//delta |Xmax - Xmin| 
// Maior delta
 for ::
ponto/= maior_delta
*/
}


void centralizaObj(Lista *listaCompleta){
  cout << "Centralizando V:" << endl;
  int n = 0;
  float x, y, z;
  float xMax = -100000, yMax = -100000, zMax = -100000;
  float xMin = 100000, yMin = 100000, zMin = 100000;
  for (auto it : listaCompleta->listaV){
    if(n==0){
      x = it;
      if(x > xMax) xMax = x;
      if(x < xMin) xMin = x;
      n++;
    }
    else if(n==1){
      y = it;
      if(y > yMax) yMax = y;
      if(y < yMin) yMin = y;
      n++;
    }
    else if(n==2){
      z = it;
      if(z > zMax) zMax = z;
      if(z < zMin) zMin = z;
      n=0;
    }
  }

  float deltaX, deltaY, deltaZ;

  deltaX = xMax - xMin;
  deltaY = yMax - yMin;
  deltaZ = zMax - zMin;
  n=0;

  for (list<float>::iterator it = listaCompleta->listaV.begin(); it != listaCompleta->listaV.end(); it++){
    if(n==0){
      *it = *it - (xMin + deltaX/2*1.0);
      //cout << "X: " << *it << endl;
      n++;
    }
    else if(n==1){
      *it = *it - (yMin + deltaY/2*1.0);
      //cout << "Y: " << *it << endl;
      n++;
    }
    else if(n==2){
      *it = *it - (zMin + deltaZ/2*1.0);
      //cout << "Z: " << *it << endl;
      n=0;
    }
  }
  cout << "Valores \txMax: " << xMax << " \tyMax: "<< yMax << " \tzMax: " << zMax << endl;
  cout << "Valores \txMin: " << xMin << " \tyMin: "<< yMin << " \tzMin: " << zMin << endl;
  cout << "Valores \tDeltaX: " << deltaX << " \tdeltaY: "<< deltaY << " \tdeltaZ: " << deltaZ;
  listaCompleta->xMax = xMax;
  listaCompleta->yMax = yMax;
  listaCompleta->zMax = zMax;

  listaCompleta->xMin = xMin;
  listaCompleta->yMin = yMin;
  listaCompleta->zMin = zMin;

  listaCompleta->deltaX= deltaX;
  listaCompleta->deltaY= deltaY;
  listaCompleta->deltaZ= deltaZ;

}
void jogaParaListaVN(double a, double b, double c, Lista *listaCompleta){
  normalizaVetor(&a,&b,&c);
  listaCompleta->listaVN.push_back(a);
  listaCompleta->listaVN.push_back(b);
  listaCompleta->listaVN.push_back(c);
}

void jogaParaListaF(string a, string b, string c, Lista *listaCompleta){
  listaCompleta->listaF.push_back(a);
  listaCompleta->listaF.push_back(b);
  listaCompleta->listaF.push_back(c);
}

void carregarArquivo(string nomeArquivo, Lista *listaCompleta){
  
  ifstream arquivo(nomeArquivo.c_str());
  cout << "Arquivo: " << nomeArquivo << endl << endl;

  if(!arquivo.is_open()){
    cout << "Não foi possível abrir o aquivo." << endl;
    exit(-1);
  }
  cout << "Arquivo aberto com sucesso!" << endl;

  string hash;
  getline(arquivo, hash);
  cout << hash << endl;
  getline(arquivo, hash);
  cout << hash << endl;

  string nome, nome1;
  string line;
  string variavel;
  float valor1, valor2, valor3;
  string associacao1, associacao2, associacao3;

  while(!arquivo.eof()){
    getline(arquivo,line);
    stringstream ss (line);
    ss >> variavel;

    if(variavel == "v"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2 >> valor3;
      jogaParaListaV(valor1,valor2,valor3, listaCompleta);
      //cout << variavel << " "<< valor1 <<" "<< valor2 <<" "<< valor3 << endl ;
    }

    if(variavel == "vt"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2;
      jogaParaListaVT(valor1,valor2, listaCompleta);
      //cout << variavel << " "<< valor1 <<" "<< valor2 <<" "<< endl ;

    }
    if(variavel == "vn"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2 >> valor3;
      jogaParaListaVN(valor1,valor2,valor3, listaCompleta);
      //cout << variavel << " " << valor1 << " " << valor2 << " " << valor3 << endl;

    }
    if(variavel == "f"){
      stringstream ss (line);
      ss >> variavel >> associacao1 >> associacao2 >> associacao3;
      jogaParaListaF(associacao1, associacao2, associacao3, listaCompleta);
      //cout << variavel << " " << associacao1 << " " << associacao2 << " " << associacao3 << endl;

    }
    if(variavel == "s"){
      stringstream ss (line);
      ss >> variavel >> valor1;
      //cout << variavel << " " << valor1 << endl ;

    }
    if(variavel == "usemtl" || variavel == "mtllib"){
      stringstream ss (line);
      ss >> variavel >> nome1;
      //cout << variavel << " " << nome1 << endl ;

    }
  }
  cout << "Leitura do arquivo concluida!" << endl << endl;
}
 /* Laço principal */
int main(){
  Lista listaCompleta;
 
  std::string nomeArgv = "Spider-Man-simples.obj";
  carregarArquivo(nomeArgv, &listaCompleta);

  centralizaObj(&listaCompleta);
  cout << endl <<endl << "Todos valores de V Centralizados:" << endl;

  int n=0;
  for (list<float>::iterator it = listaCompleta.listaV.begin(); it != listaCompleta.listaV.end(); it++){
    if(n==0){
      cout << "X: " << *it << "  ";
      n++;
    }
    else if(n==1){
      cout << "Y: " << *it << "  ";
      n++;
    }
    else if(n==2){
      cout << "Z: " << *it << "  ";
      n=0;
    }
  }
  cout << endl << endl <<"Todos valores de V Centralizados e Redimensionados:" << endl;
  redimensionaObj(&listaCompleta);
  n=0;
  for (list<float>::iterator it = listaCompleta.listaV.begin(); it != listaCompleta.listaV.end(); it++){
    if(n==0){cout << "X: " << *it << "  "; n++; }
    else if(n==1){cout << "Y: " << *it << "  "; n++; }
    else if(n==2){ cout << "Z: " << *it << "  "; n=0; }
  }

  printf("\n\nValores minimos e maximos para uma segunda centralizacao\n");
  centralizaObj(&listaCompleta);


  
  cout << endl << endl << "Todos valores de VT:" << endl;
  for (list<float>::iterator it = listaCompleta.listaVT.begin(); it != listaCompleta.listaVT.end(); it++)
    cout << *it << "  ";

  cout << endl << endl << "Todos valores de VN Normalizados:" << endl;
  for (list<double>::iterator it = listaCompleta.listaVN.begin(); it != listaCompleta.listaVN.end(); it++)
    cout << *it << "  ";

  cout << endl << endl << "Todos valores de F:" << endl;
  for (list<string>::iterator it = listaCompleta.listaF.begin(); it != listaCompleta.listaF.end(); it++)
    cout << *it << "  ";

  //normalizaVetor(1,-2,2);
  cout << endl << endl << "Encerrando programa." << endl;
  
  return 0;
}
