#ifndef __Sound_h_
#define __Sound_h_
#include "fmod.hpp"

/*
Gestiona y reproduce sonidos.
*/
class AdriSound
{
public:
	AdriSound(const char* path);
	~AdriSound();

	void TogglePaused();

	void Play();
	void Stop();
	void Pause();
	void SetVolume(float volume);
	void SetPan(float pan);

private:

	FMOD::Sound *sound;
	FMOD::Channel *channel;

};
#endif // #ifndef __Sound_h_
