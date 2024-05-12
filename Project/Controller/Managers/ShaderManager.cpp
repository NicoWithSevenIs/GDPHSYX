#include "ShaderManager.hpp"

using namespace managers;

void ShaderManager::LoadShader(std::string name, std::string path, unsigned int shader_type) {

    std::fstream shaderSrc(path);

    if (!shaderSrc.is_open()) {
        std::cout << "Failed to Load Shader: " << path;
        return;
    }

    std::stringstream shaderBuff;
    shaderBuff << shaderSrc.rdbuf();

    std::string shaderS = shaderBuff.str();
    const char* s = shaderS.c_str();

    //Initializing Shaders
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    if (!this->shaders[name]) 
        this->shaders[name] = new GLuint(glCreateProgram());
    
    glAttachShader(*this->shaders[name], shader);
}

GLuint* ShaderManager::getShader(std::string key) {
    return shaders.find(key) != shaders.end() ? shaders[key] : nullptr;
}



#pragma region Singleton

	ShaderManager* ShaderManager::Instance = nullptr;


	ShaderManager* ShaderManager::getInstance(){
		if (!Instance)
			Instance = new ShaderManager();
		return Instance;
	}

	ShaderManager::ShaderManager() {}

	ShaderManager::~ShaderManager() {}
	ShaderManager::ShaderManager(const ShaderManager&) {}



#pragma endregion