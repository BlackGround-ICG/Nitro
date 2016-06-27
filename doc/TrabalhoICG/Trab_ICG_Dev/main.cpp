#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>

using namespace std;

list<float> listaV;
list<float> listaVT;
list<float> listaVN;
list<string> listaF;

void jogaParaListaV(float a, float b, float c){
  listaV.push_back(a);
  listaV.push_back(b);
  listaV.push_back(c);
}

void jogaParaListaVT(float a, float b){
  listaVT.push_back(a);
  listaVT.push_back(b);
}

void jogaParaListaVN(float a, float b, float c){
  listaVN.push_back(a);
  listaVN.push_back(b);
  listaVN.push_back(c);
}

void jogaParaListaF(string a, string b, string c){
  listaF.push_back(a);
  listaF.push_back(b);
  listaF.push_back(c);
}

void carregarArquivo(string nomeArquivo){
  
  ifstream arquivo(nomeArquivo.c_str());
  cout << nomeArquivo << endl;

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
      jogaParaListaV(valor1,valor2,valor3);
      //cout << variavel << " "<< valor1 <<" "<< valor2 <<" "<< valor3 << endl ;
    }

    if(variavel == "vt"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2;
      jogaParaListaVT(valor1,valor2);
      //cout << variavel << " "<< valor1 <<" "<< valor2 <<" "<< endl ;

    }
    if(variavel == "vn"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2 >> valor3;
      jogaParaListaVN(valor1,valor2,valor3);
      //cout << variavel << " " << valor1 << " " << valor2 << " " << valor3 << endl;

    }
    if(variavel == "f"){
      stringstream ss (line);
      ss >> variavel >> associacao1 >> associacao2 >> associacao3;
      jogaParaListaF(associacao1, associacao2, associacao3);
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
}
 /* Laço principal */
int main(){

 
  std::string nomeArgv = "Spider-Man-simples.obj";
  carregarArquivo(nomeArgv);

  cout << "Todos valores de V:" << endl;
  for (std::list<float>::iterator it = listaV.begin(); it != listaV.end(); it++)
    cout << *it << endl;

  cout << "Todos valores de VT:" << endl;
  for (std::list<float>::iterator it = listaVT.begin(); it != listaVT.end(); it++)
    cout << *it << endl;

  cout << "Todos valores de VN:" << endl;
  for (std::list<float>::iterator it = listaVN.begin(); it != listaVN.end(); it++)
    cout << *it << endl;

  cout << "Todos valores de F:" << endl;
  for (std::list<string>::iterator it = listaF.begin(); it != listaF.end(); it++)
    cout << *it << endl;

  cout << "Encerrando programa." << endl;
  
  return 0;
}
