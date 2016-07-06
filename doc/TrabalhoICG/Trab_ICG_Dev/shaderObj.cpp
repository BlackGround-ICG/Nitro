#include "shaderObj.h"

namespace ijengine{
	ShaderObj::ShaderObj();
	ShaderObj::~ShaderObj();

	void ShaderObj::RenderSceneCB(){
	    glClear(GL_COLOR_BUFFER_BIT);

	    glEnableVertexAttribArray(0); //Posição no shader dos vértices
	    glEnableVertexAttribArray(1); //Posição no shader da textura
	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	    
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(float)*3));
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, TBO[count]);
	    
	    if (count==0){
	   		count=1;
	    }else {
	    	count=0;
	    }
	    
	    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	 	//glDrawArrays(GL_TRIANGLES, 0, 4);

	    glDisableVertexAttribArray(0);
	   	glDisableVertexAttribArray(1);

	    SDL_GL_SwapWindow(displayWindow);
	}

	void ShaderObj::CreateVertexBuffer(){

	  	Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
	                           Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
	                           Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
	                           Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };
	    glGenBuffers(1, &VBO);
	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
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

	void ShaderObj::CreateIndexBuffer(){
	    unsigned int Indices[] = { 0, 3, 1,
	                               1, 3, 2,
	                               2, 3, 0,
	                               0, 1, 2 };

	    glGenBuffers(1, &IBO);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	}

	void ShaderObj::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){
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

	void ShaderObj::CompileShaders(){
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



}