#ifndef __Sound_h_
#define __Sound_h_
#include "fmod.hpp"

/*
Gestiona y reproduce sonidos.
*/
class MySound
{
public:
	MySound(const char* path, FMOD_MODE mode);
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
	void SetVel(FMOD_VECTOR *vel);
	void SetConeOrientarion(FMOD_VECTOR *dir);	//Dirección de un sonido

	//InsideConeAngle. ángulo del cono interior. Donde no hay atenuación. Por defecto 360
	//OutsideConeAngle. Ángulo del cono exterior. Donde el sonido se atenúa. Se calcua por interpolación. Por defecto 360
	//OutsiudeVolume. Volumen fuera del cono exteior. Por defecto 1.0
	void SetConeSettings(float insideConeAngle, float outsideconeangle, float outsidevolume);	//Angulos en grados

	void FadeIn(float time);
	void FadeOut(float time);

	//Controla la atenuación
	//minDistance: distancia a partir de la cual el sonido comienza a atenuarse
	//maxDistance: distancia a partir de la cual el sonido no se atenúa más
	void SetMinMaxDistance(float minDistance, float maxDistance);

private:

	FMOD::Sound *sound;
	FMOD::Channel *channel;

};
#endif // #ifndef __Sound_h_
