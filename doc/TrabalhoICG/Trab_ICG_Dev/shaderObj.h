#ifndef SHADEROBJ_H
#define SHADEROBJ_H

#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include <math.h>

namespace ijengine{

	class ShaderObj{
		public:
			
			ShaderObj();
			~ShaderObj();
			const char* pVSFileName = "shader.vs";
			const char* pFSFileName = "shader.fs";
			void RenderSceneCB();
			void CreateVertexBuffer();
			void CreateIndexBuffer();
			void ShaderObj::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
			void ShaderObj::CompileShaders();



	};

}
#endif