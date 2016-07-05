
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


SDL_Window* displayWindow;

GLuint VBO, TBO,IBO;
int gSampler;

//1 - Alterar a estrutura de dados do vértice (inserir Vector2f em math_3d.h)
struct Vertex
{
   //insira seu código aqui
    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
    // insira seu código aqui
    }
};

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
static void CreateIndexBuffer();

static void RenderSceneCB()
{
// 3 - Loop do jogo - habilita o uso da textura para ser usado no shader
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0); //Posição no shader dos vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

  
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(displayWindow);
}

//2 - Criar o buffer de vértices formando o objeto
static void CreateVertexBuffer()
{

//2.1 - Inserir dados referentes ao vértice - localização e coordenada da textura
  Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                           Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
                           Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                           Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

// 2.2 - Variável uniforme - id da imagem/textura utilizada no mapeamento
    glUniform1i(gSampler, 0);


// 2.3 Ler imagem e transformá-la em textura
    SDL_Surface * image = SDL_LoadBMP("images.bmp");
  
    if(image == NULL){
	printf("\n Erro ao ler a imagem de textura %s\n", SDL_GetError());
    }
    int Mode = GL_RGB;
    if(image->format->BytesPerPixel == 4) {
   	 Mode = GL_RGBA;
    }
//2.4 - Configurar Textura para ser processado no shader
  
	//insira seu código aqui

}

static void CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
printf("\n Create index ok");
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
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


static void CompileShaders()
{
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
//    assert(gSampler != 0xFFFFFFFF);
}

 /* Laço principal */
int
main()
{
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
    RenderSceneCB();	
    
    SDL_Delay(5000);
    SDL_Quit();
    
    return 0;
}
