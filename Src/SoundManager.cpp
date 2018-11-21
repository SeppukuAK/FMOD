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

void SoundManager::SetListener(int id, FMOD_VECTOR * pos, FMOD_VECTOR * vel, FMOD_VECTOR * up, FMOD_VECTOR * at)
{
	ERRCHECK(system->set3DListenerAttributes(id, pos, vel, up, at));
}

void SoundManager::SetListenerPos(FMOD_VECTOR *pos)
{
	FMOD_VECTOR *vel = nullptr, *forward = nullptr, *up = nullptr;
	ERRCHECK (system->get3DListenerAttributes(0, nullptr, vel, forward, up));
	ERRCHECK( system->set3DListenerAttributes(0, pos, vel, forward, up));
}

void SoundManager::SetNumListeners(int num)
{
	ERRCHECK(system->set3DNumListeners(num));
}

void SoundManager::SetDoppler(float newValue)
{
	float distanceFactor, rolloffScale;

	ERRCHECK(system->get3DSettings(nullptr, &distanceFactor, &rolloffScale));
	ERRCHECK(system->set3DSettings(newValue, distanceFactor, rolloffScale));
}

void SoundManager::SetRolloff(float newValue)
{
	float doppler, distanceFactor;

	ERRCHECK(system->get3DSettings(&doppler, &distanceFactor, nullptr));
	ERRCHECK(system->set3DSettings(doppler, distanceFactor, newValue));
}

void SoundManager::SetDistanceFactor(float newValue)
{
	float doppler, rolloffScale;

	ERRCHECK(system->get3DSettings(&doppler, nullptr, &rolloffScale));
	ERRCHECK(system->set3DSettings(doppler, newValue, rolloffScale));
}

//Facilita la gestión de errores
void SoundManager::ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}