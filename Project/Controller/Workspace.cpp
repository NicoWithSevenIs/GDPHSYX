#include "Workspace.hpp"

bool  Workspace::Awake() {

	if (!glfwInit())
		return false;

	this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Nico Tolentino", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(this->window);
	gladLoadGL();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	return true;

}

void Workspace::Initialize() {
}

void Workspace::Draw(){
}


void Workspace::Update(float deltaTime){
}




void Workspace::Run() {
	
	if (!this->Awake()) {
		std::cout << "Aborted. Failed Window Creation";
		return;
	}		
	
	std::chrono::steady_clock::time_point timeSinceLastUpdate = std::chrono::steady_clock::now();

	this->Initialize();

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> deltaTime = currentTime - timeSinceLastUpdate;
		timeSinceLastUpdate = currentTime;


		this->Update(deltaTime.count());
		this->Draw();

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	glfwTerminate();

}

#pragma region Singleton
	Workspace* Workspace::Instance = nullptr;

	Workspace::Workspace() {}
	Workspace::Workspace(const Workspace&) {}

	Workspace* Workspace::getInstance() {
		if (!Instance)
			Instance = new Workspace();
		return Instance;
	}
#pragma endregion

