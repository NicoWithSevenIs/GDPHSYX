#include "CameraManager.hpp"

using namespace managers;


Camera* CameraManager::getCamera() {
	return getInstance()->currentCamera;
}

CameraManager* CameraManager::instance = nullptr;

CameraManager* CameraManager::getInstance() {
	if (!instance) 
		instance = new CameraManager();
	return instance;
}

CameraManager::CameraManager() {
	this->ortho = OrthographicCamera();
	this->currentCamera = &this->ortho;
}


CameraManager::CameraManager(const CameraManager&){}