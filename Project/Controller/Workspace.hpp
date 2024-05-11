#pragma once

#include "../../config.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

class Workspace {

		private:
			GLFWwindow* window;


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