#pragma once

#include "../Interfaces/ICamera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace interfaces;

class OrthographicCamera : public ICamera {
	
	private:
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;

		float ZNear;
		float ZFar;
		float size;

	public:
		void Render();
		glm::vec3 getCameraPos();
		glm::vec3 getCameraFront();


	#pragma region Singleton
	private:
		static OrthographicCamera* Instance;

	public:
		static OrthographicCamera* getInstance();

	private:
		OrthographicCamera(glm::vec3 pos, glm::vec3 front, float ZNear, float ZFar, float size);
		OrthographicCamera(const OrthographicCamera&);
		OrthographicCamera& operator = (const OrthographicCamera&);
	#pragma endregion

};