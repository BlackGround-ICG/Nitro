
/*
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ogldev_util.h"
#include "math_3d.h"
#include "vec.h"
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"

//Mesh mesh;
/*
struct v e vn{
  valor 1 2 3
}
struct vt {
  valor 1 2 
}
struct f {
  string 1 2 3 
}
*/


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

  string nome;
  string line;
  string variavel;
  float valor1, valor2, valor3;
  string associacao1, associacao2, associacao3;

  getline(arquivo,line);
  stringstream ss (line);
   ss >> valor1 >> valor2 >> valor3;
  cout << line << endl;

  while(!arquivo.eof()){

    if(variavel == "v"){
      //joga os valores 1, 2 e 3 pra uma lista;
      //cout << variavel << valor1 << valor2 << valor3 << endl;
      ss >> valor1 >> valor2 >> valor3;
      getline(arquivo,line);
      ss >> variavel;
    }
    if(variavel == "vt"){
      ss >> valor1 >> valor2;
      cout << variavel << " " << valor1 << " " << valor2 << endl;      
      
      getline(arquivo,line);
      ss >> variavel;
    }
    if(variavel == "vn"){
      ss >> valor1 >> valor2 >> valor3;
      getline(arquivo,line);
      ss >> variavel;
    }
    if(variavel == "f"){
      ss >> associacao1 >> associacao2 >> associacao3;
      getline(arquivo,line);
      ss >> variavel;
    }
    if(variavel == "s"){
      ss >> valor1;
      getline(arquivo, line);
      ss >> variavel;
    }else{
      //a variavel é um nome
      getline(arquivo, line);
      cout << line << endl;
      ss >> variavel;
    }




  }
   


}
 /* Laço principal */
int main(){
   
    std::string nomeArgv = "Spider-Man-simples.obj";
    carregarArquivo(nomeArgv);
    cout << "Encerrando programa." << endl;
    
    return 0;
}
