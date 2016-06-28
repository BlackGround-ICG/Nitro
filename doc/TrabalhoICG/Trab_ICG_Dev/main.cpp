#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>

using namespace std;
using namespace ijengine;

Mesh mesh;

 /* Laço principal */
int main(){

  string nomeArgv = "Spider-Man-simples.obj";
  mesh.carregarArquivo(nomeArgv);

  cout << "Todos valores de V:" << endl;
  for (auto it : mesh.lista.listaV)
    cout << it << endl;

  cout << "Todos valores de VT:" << endl;
  for (auto it : mesh.lista.listaVT)
    cout << it << endl;

  cout << "Todos valores de VN:" << endl;
  for (auto it : mesh.lista.listaVN)
    cout << it << endl;

  cout << "Todos valores de F:" << endl;
  for (auto it : mesh.lista.listaF)
    cout << it << endl;

  //normalizaVetor(1,-2,2);
  cout << "Encerrando programa." << endl;

  return 0;
}
