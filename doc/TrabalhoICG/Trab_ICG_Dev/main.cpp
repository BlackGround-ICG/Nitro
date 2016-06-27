
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
   getline(arquivo, nome);
   cout << nome << endl;

  string line;
  string variavel;
  float valor1, valor2, valor3;
  getline(arquivo,line);
  stringstream ss (line);
  ss >> variavel >> valor1 >> valor2 >> valor3;

  cout << variavel << endl;
  cout << valor1 << endl;
  cout << valor2 << endl;
  cout << valor3 << endl;



}
 /* Laço principal */
int main(){
   
    std::string nomeArgv = "Spider-Man.obj";
    carregarArquivo(nomeArgv);
    cout << "Encerrando programa." << endl;
    
    return 0;
}
