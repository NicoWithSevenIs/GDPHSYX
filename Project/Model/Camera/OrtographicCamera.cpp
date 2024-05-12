#include "OrtographicCamera.hpp"

void OrthographicCamera::Render() {

	/*
	GLuint cameraPosAddress = glGetUniformLocation(*ShaderManager::getModelShader(), "cameraPos");
	glUniform3fv(cameraPosAddress, 1, glm::value_ptr(this->cameraPos));

	this->viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


	this->projectionMatrix = glm::ortho(
		 this->orthoData.left,
		 this->orthoData.right,
		 this->orthoData.bottom,
		 this->orthoData.top,
		 this->orthoData.znear,
		 this->orthoData.zfar
	 );



	auto modelShader = ShaderManager::getModelShader();

	unsigned int projectionLoc = glGetUniformLocation(*modelShader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

	unsigned int viewLoc = glGetUniformLocation(*modelShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	*/


}

glm::vec3 OrthographicCamera::getCameraPos() {
	return this->cameraPos;
}

glm::vec3 OrthographicCamera::getCameraFront() {
	return this->cameraFront;
}


#pragma region Singleton
	OrthographicCamera* OrthographicCamera::Instance = nullptr;

	OrthographicCamera* OrthographicCamera::getInstance() {
		if(!Instance)
			Instance = new OrthographicCamera(glm::vec3(0,0,0), glm::vec3(0,0,0), 1, 100, 5);
		return Instance;
	}

	//temp - will make a camera manager when i feel like it
	OrthographicCamera::OrthographicCamera(glm::vec3 pos, glm::vec3 front, float ZNear, float ZFar, float size) {
		this->cameraPos = pos;
		this->cameraFront = front;
		this->ZNear = ZNear;
		this->ZFar = ZFar;
		this->size = size;
	}

	OrthographicCamera::OrthographicCamera(const OrthographicCamera& c) {
		this->cameraPos = c.cameraPos;
		this->cameraFront = c.cameraFront;
		this->ZNear = c.ZNear;
		this->ZFar = c.ZFar;
		this->size = c.size;
	}

#pragma endregion
