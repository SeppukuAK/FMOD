#ifndef __SoundManager_h_
#define __SoundManager_h_
#include "fmod.hpp"


class SoundManager
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static SoundManager *instance;

public:
	/* Static access method. */
	static SoundManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	SoundManager();
	~SoundManager();

public:
	inline FMOD::System* GetSystem() { return system; };

	void Update();

	//Listener methods
	void SetListener(int id, FMOD_VECTOR * pos, FMOD_VECTOR * vel, FMOD_VECTOR * up, FMOD_VECTOR * at);
	void SetListenerPos(FMOD_VECTOR *pos);
	void SetNumListeners(int num);			//Establece el número de listeners

	//Parámetros del globales
	void SetRolloff(float newValue);	//Atenuación con la distancia
	void SetDoppler(float newValue);	//Variación de frecuencia por la velocidad
	void SetDistanceFactor(float newValue);	//Dimensiones del escenario

	static void ERRCHECK(FMOD_RESULT result);	//Facilita la gestión de errores

private:
	FMOD::System *system;

};
#endif // #ifndef __SoundManager_h_
