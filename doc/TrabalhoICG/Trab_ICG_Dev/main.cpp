#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
using namespace ijengine;

Mesh mesh;

SDL_Window* displayWindow;

 /* Laço principal */
int main(){

  string nomeArgv = "Spider-Man-simples.obj";

  mesh.carregarArquivo(nomeArgv);
  mesh.centralizaObj();

  cout << endl <<endl << "Todos valores de V Centralizados:" << endl;

  int n=0;
  for (auto it : mesh.lista.listaV){
    if(n==0){
      cout << "X: " << it << "  ";
      n++;
    }
    else if(n==1){
      cout << "Y: " << it << "  ";
      n++;
    }
    else if(n==2){
      cout << "Z: " << it << "  ";
      n=0;
    }
  }

  mesh.redimensionaObj();

  n=0;

  for (auto it : mesh.lista.listaV){
    if(n==0){cout << "X: " << it << "  "; n++; }
    else if(n==1){cout << "Y: " << it << "  "; n++; }
    else if(n==2){ cout << "Z: " << it << "  "; n=0; }
  }

  printf("\n\nValores minimos e maximos para uma segunda centralizacao\n");

  mesh.centralizaObj();

  cout << endl << endl << "Todos valores de VT:" << endl;
  for (auto it : mesh.lista.listaVT)
    cout << it << " ";

  cout << endl << endl << "Todos valores de VN:" << endl;
  for (auto it : mesh.lista.listaVN)
    cout << it << " ";

  cout << endl << endl << "Todos valores de F:" << endl;
  for (auto it : mesh.lista.listaF)
    cout << it << " ";

  cout << endl << endl;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Renderer* displayRenderer;
  int flags = SDL_WINDOW_OPENGL;
  atexit(SDL_Quit);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_CreateWindowAndRenderer(1024, 768, flags,&displayWindow, &displayRenderer);

  SDL_GL_CreateContext(displayWindow);
  /*
  GLenum res = glewInit();
  if (glewIsSupported("GL_VERSION_3_3"))
    printf("Ready for OpenGL 3.3\n");
  else {
    printf("OpenGL 3.3 not supported\n");
    exit(1);
  }
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    CreateVertexBuffer();
    CreateIndexBuffer();
    CompileShaders();
    int i=20;
    while (i--){
      RenderSceneCB();  
      
      SDL_Delay(500);
  }
    SDL_Quit();
    */
    

  return 0;
}
