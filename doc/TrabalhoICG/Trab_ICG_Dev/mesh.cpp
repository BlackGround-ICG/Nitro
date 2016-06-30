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

  void Mesh::centralizaObj(){
    int n = 0;
    float x, y, z;
    float xMax = -100000, yMax = -100000, zMax = -100000;
    float xMin = 100000, yMin = 100000, zMin = 100000;

    cout << "Centralizando V:" << endl;

    for (auto it : lista.listaV){
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

    for (auto it : lista.listaV){
      if(n==0){
        it = it - (xMin + deltaX/2*1.0);
        //cout << "X: " << *it << endl;
        n++;
      }
      else if(n==1){
        it = it - (yMin + deltaY/2*1.0);
        //cout << "Y: " << *it << endl;
        n++;
      }
      else if(n==2){
        it = it - (zMin + deltaZ/2*1.0);
        //cout << "Z: " << *it << endl;
        n=0;
      }
    }
    cout << "Valores \txMax: " << xMax << " \tyMax: "<< yMax << " \tzMax: " << zMax << endl;
    cout << "Valores \txMin: " << xMin << " \tyMin: "<< yMin << " \tzMin: " << zMin << endl;
    cout << "Valores \tDeltaX: " << deltaX << " \tdeltaY: "<< deltaY << " \tdeltaZ: " << deltaZ;
    lista.Xmax = xMax;
    lista.Ymax = yMax;
    lista.Zmax = zMax;

    lista.Xmin = xMin;
    lista.Ymin = yMin;
    lista.Zmin = zMin;

    lista.deltaX= deltaX;
    lista.deltaY= deltaY;
    lista.deltaZ= deltaZ;

}

  void Mesh::redimensionaObj(){
    //ver maior delta
    float maiorDelta = -100000;

    if(lista.deltaX > maiorDelta) maiorDelta = lista.deltaX;
    if(lista.deltaY > maiorDelta) maiorDelta = lista.deltaY;
    if(lista.deltaZ > maiorDelta) maiorDelta = lista.deltaZ;

    for (auto it : lista.listaV){
      it = it/maiorDelta*1.0;
    }
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
