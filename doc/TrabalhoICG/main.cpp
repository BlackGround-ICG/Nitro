
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "ogldev_util.h"
#include "math_3d.h"
#include "vec.h"
#include "mesh.h"


SDL_Window* displayWindow;

Mesh mesh;

GLuint VBO;
GLuint EBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, mesh.getIndice().size(), GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_POINTS, 0, mesh.getVertex().size());

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(displayWindow);
}


static void CreateVertexBuffer()
{
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertex().size() * sizeof(Vertex), &mesh.getVertex()[0], GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndice().size() * sizeof(unsigned int), &mesh.getIndice()[0], GL_STATIC_DRAW);
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
}

bool handleEvent(){

    bool exitSuccess = false;
    SDL_Event sdlEvent;

    while(SDL_PollEvent(&sdlEvent)){
            
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
            }
    } 
    return exitSuccess;
}

 /* Laço principal */
int
main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "Deve-se passar o nome do arquivo .off juntamente com o nome do programa!!!" << endl;
        exit(-1);
    }

    mesh.carregarArquivo(argv[1]);
    mesh.transladar();
    mesh.redimensionar();

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

    CompileShaders();

    do{
    RenderSceneCB();	
    bool exitSuccess = handleEvent();

    if(exitSuccess){
            break;
        }

    }while(true);
    
    return 0;
}
