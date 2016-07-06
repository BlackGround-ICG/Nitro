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

GLuint VBO, TBO[2],IBO;
int gSampler, count=0;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
static void CreateIndexBuffer();

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0); //Posição no shader dos vértices
    glEnableVertexAttribArray(1); //Posição no shader da textura
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh.lista.listaV), 0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(mesh.lista.listaVT), (const GLvoid*)(sizeof(float)*3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TBO[count]);
    
    if (count==0){
      count=1;
    }else {
      count=0;
    }
  
    glDrawElements(GL_TRIANGLES, sizeof(mesh.lista.listaV), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    SDL_GL_SwapWindow(displayWindow);
}


static void CreateVertexBuffer(){

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.lista.listaV), &mesh.lista.listaV, GL_STATIC_DRAW);
    //Textura

    glUniform1i(gSampler, 0);
    SDL_Surface * image = SDL_LoadBMP("images.bmp");

    
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

    image = SDL_LoadBMP("test.bmp");

    
    if(image == NULL){
      printf("\n Erro ao ler a imagem de textura %s\n", SDL_GetError());
    }
    Mode = GL_BGR;
    if(image->format->BytesPerPixel == 4) {
     Mode = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, TBO[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,Mode, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

static void CreateIndexBuffer(){
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders(){
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
      glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
      fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
          exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
    gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
}

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
  CreateVertexBuffer();

  CreateIndexBuffer();
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
