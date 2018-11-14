#ifndef __Sound_h_
#define __Sound_h_
#include "fmod.hpp"

/*
Gestiona y reproduce sonidos.
*/
class MySound
{
public:
	MySound(const char* path);
	~MySound();

	void TogglePaused();

	void Play();
	void Stop();
	void Pause();
	void SetVolume(float volume);
	void SetPan(float pan);
	void SetPitch(float pitch);
	void SetLoop(bool loop);

	void SetPos(FMOD_VECTOR *pos);
	void SetConeOrientarion(FMOD_VECTOR *dir);
	void SetConeSettings(float insideConeAngle, float outsideconeangle, float outsidevolume);

	void FadeIn(float time);
	void FadeOut(float time);

private:

	FMOD::Sound *sound;
	FMOD::Channel *channel;

};
#endif // #ifndef __Sound_h_
