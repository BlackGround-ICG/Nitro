#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>

using namespace std;

list<float> listaV;


void jogaParaListaV(float a, float b, float c){
  listaV.push_back(a);
  listaV.push_back(b);
  listaV.push_back(c);
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
      //cout << variavel << " "<< valor1 <<" "<< valor2 <<" "<< endl ;

    }
    if(variavel == "vn"){
      stringstream ss (line);
      ss >> variavel >> valor1 >> valor2 >> valor3;
      //cout << variavel << " " << valor1 << " " << valor2 << " " << valor3 << endl;

    }
    if(variavel == "f"){
      stringstream ss (line);
      ss >> variavel >> associacao1 >> associacao2 >> associacao3;
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

    cout << "Todos valores de vertices:" << endl;
    for (std::list<float>::iterator it = listaV.begin(); it != listaV.end(); it++)
      cout << *it << endl;

    cout << "Encerrando programa." << endl;
    
    return 0;
}
