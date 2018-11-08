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

	static void ERRCHECK(FMOD_RESULT result);	//Facilita la gestión de errores

private:
	FMOD::System *system;

};
#endif // #ifndef __SoundManager_h_
