#include "Sound.h"
#include "SoundManager.h"


AdriSound::AdriSound(const char* path)
{
	sound = nullptr;
	channel = nullptr;

	FMOD_RESULT result = SoundManager::GetInstance()->GetSystem()->createSound(
		path,
		FMOD_DEFAULT | FMOD_LOOP_NORMAL, // valores (por defecto: sin loop, 2D) Existen más alternativas
		0, // informacion adicional (nada en este caso)
		&sound);
	SoundManager::ERRCHECK(result);

	////Posiciona en el tiempo 
	//channel->setPosition(0, FMOD_TIMEUNIT_MS); //Medio segundo después

	//// se repite indefinidamente
	//channel->setLoopCount(-1);
	//// Se repite una sola vez
	////channel->setLoopCount(0);
	//// Tres veces
	////channel->setLoopCount(2);

	////channel->setMute(true); Silencia/activa el canal.

	////Modifica el volumen de sonidos multicanal. Por ejemplo en un sonido estéreo
	////channel->setMixLevelsOutput(frontleft, frontright, center, ..., backleft, backright);

	////channel->setPicth(2.0f);
	////channel->setFrequency(rateHz);
}

AdriSound::~AdriSound()
{
	//Libera el buffer de sonido
	SoundManager::ERRCHECK(sound->release());
}

void AdriSound::Play()
{
	//Reproducción del sonido
	FMOD_RESULT result = SoundManager::GetInstance()->GetSystem()->playSound(
		sound,
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca con "pause" 
		&channel);
	SoundManager::ERRCHECK(result);

	SoundManager::ERRCHECK(channel->setLoopCount(0));
}

void AdriSound::Stop()
{
	if (channel != nullptr)
	{
		SoundManager::ERRCHECK(channel->stop());
		channel = nullptr;
	}
}

void AdriSound::Pause()
{
	SoundManager::ERRCHECK(channel->setPaused(true));
}

void AdriSound::SetVolume(float volume)
{
	SoundManager::ERRCHECK(channel->setVolume(volume));
}

void AdriSound::SetPan(float pan)
{
	SoundManager::ERRCHECK(channel->setPan(pan));
}

//Método para pausa o despausar el audio
void AdriSound::TogglePaused() {
	bool paused;
	if (channel != nullptr)
	{
		SoundManager::ERRCHECK(channel->getPaused(&paused));
		SoundManager::ERRCHECK(channel->setPaused(!paused));
	}
}
