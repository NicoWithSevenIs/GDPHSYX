#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>

namespace managers {

	class ShaderManager {

		private:
			std::unordered_map<std::string, GLuint*> shaders;

		public:
			void LoadShader(std::string key, std::string path, unsigned int shader_type);
			GLuint* getShader(std::string key);


		#pragma region Singleton

		private:
			static ShaderManager* Instance;
			static ShaderManager* getInstance();

		private:
			ShaderManager();
			~ShaderManager();
			ShaderManager(const ShaderManager&);
			ShaderManager& operator = (const ShaderManager&);


		#pragma endregion


	};

}

