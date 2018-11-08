#include "SoundManager.h"
#include <iostream>
#include "fmod_errors.h" // para manejo de errores

#pragma region Singleton  

/* Null, because instance will be initialized on demand. */
SoundManager* SoundManager::instance = 0;

SoundManager* SoundManager::GetInstance()
{
	if (instance == 0)
		instance = new SoundManager();

	return instance;
}

void SoundManager::ResetInstance() {
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton


SoundManager::SoundManager()
{
	// Creamos el objeto system
	ERRCHECK(System_Create(&system));

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	ERRCHECK(system->init(128, FMOD_INIT_NORMAL, 0));	// Inicializacion de FMOD
}

SoundManager::~SoundManager()
{
	//Cierra el sistema
	ERRCHECK(system->release());
}

void SoundManager::Update()
{
	ERRCHECK(system->update());

}

//Facilita la gestión de errores
void SoundManager::ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		//printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}