#pragma once

#include "../../config.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "../Model/Interfaces/ICamera.hpp"

#include <iostream>
#include <chrono>

using namespace interfaces;
class Workspace {

		private:
			GLFWwindow* window;
			ICamera* currentCamera;

		private:
			void Draw();
			void Update(float deltaTime);
			void Initialize();
			bool Awake();

		public:
			void Run();

	#pragma region Singleton
		private:
			static Workspace* Instance;

		public:
			static Workspace* getInstance();

		private:
			Workspace();
			Workspace(const Workspace&);
			Workspace& operator = (const Workspace&);
	#pragma endregion

};