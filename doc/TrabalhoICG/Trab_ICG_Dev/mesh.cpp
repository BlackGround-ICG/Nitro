#include "mesh.h"

namespace ijengine {

  Mesh::Mesh(){}
  Mesh::~Mesh(){}

  void Mesh::carregarArquivo(string nomeArquivo){

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

  void Mesh::jogaParaListaV(float a, float b, float c){
    lista.listaV.push_back(a);
    lista.listaV.push_back(b);
    lista.listaV.push_back(c);
  }

  void Mesh::jogaParaListaVT(float a, float b){
    lista.listaVT.push_back(a);
    lista.listaVT.push_back(b);
  }

  void Mesh::normalizaVetor(double *a, double *b, double *c){
    double norma = 0;
    norma = sqrt(pow(*a,2) + pow(*b,2) + pow(*c,2));
    *a = *a/norma*1.0;
    *c = *b/norma*1.0;
    *c = *c/norma*1.0;
    //printf("Normalizados: A -> %.5lf B -> %.5lf C -> %.5lf\n",*a,*b,*c);
  }

  void Mesh::jogaParaListaVN(double a, double b, double c){
    normalizaVetor(&a,&b,&c);
    lista.listaVN.push_back(a);
    lista.listaVN.push_back(b);
    lista.listaVN.push_back(c);
  }

  void Mesh::jogaParaListaF(string a, string b, string c){
    lista.listaF.push_back(a);
    lista.listaF.push_back(b);
    lista.listaF.push_back(c);
  }
}
