#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "ogldev_util.h"
#include "math_3d.h"



using namespace std;
using namespace ijengine;

Mesh mesh;

SDL_Window* displayWindow;

GLuint VBO[3], TBO[1], IBO, VAO;
int gSampler, count=0;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB(){
  glClear(GL_COLOR_BUFFER_BIT);
  glEnableVertexAttribArray(0); //Posição no shader dos vértices
  glEnableVertexAttribArray(1); //Posição no shader da textura
  glEnableVertexAttribArray(2); //Posição no shader da normal

  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawElements(GL_TRIANGLES, sizeof(mesh.lista.listaV), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  SDL_GL_SwapWindow(displayWindow);
}


static void CreateVertexBuffer(Mesh mesh){
  glGenBuffers(1, &VAO);
  glGenBuffers(3, &VBO[3]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.lista.listaV),  &mesh.lista.listaV, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.lista.listaVN),  &mesh.lista.listaVN, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.lista.listaVT), &mesh.lista.listaVT, GL_STATIC_DRAW);
   
  glUniform1i(gSampler, 0);
  
  SDL_Surface * image = SDL_LoadBMP("homemaranha.bmp");
  if(image == NULL){
    printf("\n Erro ao ler a imagem de textura %s\n", SDL_GetError());
  }
  int Mode = GL_BGR;
  if(image->format->BytesPerPixel == 4) {
    Mode = GL_RGBA;
  }

  glGenTextures(2, &TBO[0]);
  glBindTexture(GL_TEXTURE_2D, TBO[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,Mode, GL_UNSIGNED_BYTE, image->pixels);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

int main(){

  string nomeArgv = "Spider-Man-simples.obj";

  mesh.carregarArquivo(nomeArgv);
  mesh.centralizaObj();

  cout << endl <<endl << "Todos valores de V Centralizados:" << endl;

  int n=0;
  for (auto it : mesh.lista.listaV){
    if(n==0){cout << "X: " << it << "  "; n++; }
    else if(n==1){ cout << "Y: " << it << "  "; n++; }
    else if(n==2){ cout << "Z: " << it << "  "; n=0; }
  }

  mesh.redimensionaObj();

  n=0;

  for (auto it : mesh.lista.listaV){
    if(n==0){cout << "X: " << it << "  "; n++; }
    else if(n==1){cout << "Y: " << it << "  "; n++; }
    else if(n==2){ cout << "Z: " << it << "  "; n=0; }
  }

  cout << endl << endl << "Todos valores de VT:" << endl;
  for (auto it : mesh.lista.listaVT)
    cout << it << " ";

  cout << endl << endl << "Todos valores de VN:" << endl;
  for (auto it : mesh.lista.listaVN)
    cout << it << " ";

  cout << endl << endl << "Todos valores de F:" << endl;
  for (auto it : mesh.lista.listaF)
    cout << it << " ";

  cout << endl << endl << "Inicializando Janela do Objeto" << endl <<endl;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Renderer* displayRenderer;

  int flags = SDL_WINDOW_OPENGL;
  int pendingEvent;
  SDL_Event sdlEvent;
  bool exitSuccess = false;
  atexit(SDL_Quit);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_CreateWindowAndRenderer(1024, 768, flags,&displayWindow, &displayRenderer);

  SDL_GL_CreateContext(displayWindow);
  GLenum res = glewInit();

  if (res != GLEW_OK) {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  CreateVertexBuffer(mesh);

  //CreateIndexBuffer();
  //CompileShaders();

  while(exitSuccess == false){
    
    RenderSceneCB();

    exitSuccess = false;
      
    pendingEvent = SDL_PollEvent(&sdlEvent);

    if(sdlEvent.type == SDL_KEYDOWN){
      if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
        exitSuccess = true;
      }
    }
    else if(sdlEvent.type == SDL_QUIT){
      exitSuccess = true;
    }

    if(exitSuccess == true){
      SDL_Quit();
      break;
    }

  }   
    
  cout << "Encerrando..." << endl << endl;

  return 0;
}
