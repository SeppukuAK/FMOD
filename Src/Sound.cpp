#include "Sound.h"
#include "SoundManager.h"

void AdriSound::FadeIn(float time)
{
	unsigned long long dspclock;
	SoundManager::ERRCHECK(channel->getDSPClock(0, &dspclock));

	int rate;
	SoundManager::ERRCHECK(SoundManager::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	channel->addFadePoint(dspclock, 0.0f);                 // Add a fade point at 'now' with full volume.
	channel->addFadePoint(dspclock + (rate * time), 1.0f);    // Add a fade point 5 seconds later at 0 volume.
}

void AdriSound::FadeOut(float time)
{
	unsigned long long dspclock;
	SoundManager::ERRCHECK(channel->getDSPClock(0, &dspclock));

	int rate;
	SoundManager::ERRCHECK(SoundManager::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	channel->addFadePoint(dspclock, 1.0f);                 // Add a fade point at 'now' with full volume.
	channel->addFadePoint(dspclock + (rate * time), 0.0f);    // Add a fade point 5 seconds later at 0 volume.
}

AdriSound::AdriSound(const char* path)
{
	sound = nullptr;
	channel = nullptr;

	FMOD_RESULT result = SoundManager::GetInstance()->GetSystem()->createSound(
		path,
		FMOD_DEFAULT | FMOD_LOOP_NORMAL, // valores (por defecto: sin loop, 2D) Existen m�s alternativas
		0, // informacion adicional (nada en este caso)
		&sound);
	SoundManager::ERRCHECK(result);

	////Posiciona en el tiempo 
	//channel->setPosition(0, FMOD_TIMEUNIT_MS); //Medio segundo despu�s

	//// se repite indefinidamente
	//channel->setLoopCount(-1);
	//// Se repite una sola vez
	////channel->setLoopCount(0);
	//// Tres veces
	////channel->setLoopCount(2);

	////channel->setMute(true); Silencia/activa el canal.

	////Modifica el volumen de sonidos multicanal. Por ejemplo en un sonido est�reo
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
	//Reproducci�n del sonido
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

void AdriSound::SetPitch(float pitch)
{
	SoundManager::ERRCHECK(channel->setPitch(pitch));
}

//M�todo para pausa o despausar el audio
void AdriSound::TogglePaused() {
	bool paused;
	if (channel != nullptr)
	{
		SoundManager::ERRCHECK(channel->getPaused(&paused));
		SoundManager::ERRCHECK(channel->setPaused(!paused));
	}
}
