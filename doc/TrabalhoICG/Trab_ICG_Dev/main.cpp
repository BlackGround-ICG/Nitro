
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
  
  if(!arquivo.is_open()){
    cout << "Não foi possível abrir o aquivo!!!" << endl;
    exit(-1);
  }

}
 /* Laço principal */
int main(){
   

    std::string nomeArgv = "spiderman.obj";

    carregarArquivo(nomeArgv);
    
    return 0;
}
