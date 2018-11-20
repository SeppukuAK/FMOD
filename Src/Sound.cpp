#include "Sound.h"
#include "SoundManager.h"



MySound::MySound(const char* path)
{
	sound = nullptr;
	channel = nullptr;

	FMOD_RESULT result = SoundManager::GetInstance()->GetSystem()->createSound(
		path,
		FMOD_3D | FMOD_LOOP_NORMAL, // valores (por defecto: sin loop, 2D) Existen más alternativas
		0, // informacion adicional (nada en este caso)
		&sound);
	SoundManager::ERRCHECK(result);

	//TODO: ARRANCAR CANAL EN PAUSE


	////Posiciona en el tiempo 
	//channel->setPosition(0, FMOD_TIMEUNIT_MS); //Medio segundo después

	////channel->setMute(true); Silencia/activa el canal.

	////Modifica el volumen de sonidos multicanal. Por ejemplo en un sonido estéreo
	////channel->setMixLevelsOutput(frontleft, frontright, center, ..., backleft, backright);

	////channel->setFrequency(rateHz);
}

MySound::~MySound()
{
	//Libera el buffer de sonido
	SoundManager::ERRCHECK(sound->release());
}

void MySound::Play()
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

void MySound::Stop()
{
	if (channel != nullptr)
	{
		SoundManager::ERRCHECK(channel->stop());
		channel = nullptr;
	}
}

void MySound::Pause()
{
	SoundManager::ERRCHECK(channel->setPaused(true));
}

void MySound::SetVolume(float volume)
{
	SoundManager::ERRCHECK(channel->setVolume(volume));
}

//Se utiliza para sonidos 2D: -1 Izq, O por defecto, 1 derecha
void MySound::SetPan(float pan)
{
	SoundManager::ERRCHECK(channel->setPan(pan));
}

void MySound::SetPitch(float pitch)
{
	SoundManager::ERRCHECK(channel->setPitch(pitch));
}

void MySound::SetLoop(bool loop)
{
	if (loop)
		SoundManager::ERRCHECK(channel->setLoopCount(-1));
	else
		SoundManager::ERRCHECK(channel->setLoopCount(0));

}


//Método para pausa o despausar el audio
void MySound::TogglePaused() {
	bool paused;
	if (channel != nullptr)
	{
		SoundManager::ERRCHECK(channel->getPaused(&paused));
		SoundManager::ERRCHECK(channel->setPaused(!paused));
	}
}

void MySound::FadeIn(float time)
{
	unsigned long long dspclock;
	SoundManager::ERRCHECK(channel->getDSPClock(0, &dspclock));

	int rate;
	SoundManager::ERRCHECK(SoundManager::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	channel->addFadePoint(dspclock, 0.0f);                 // Add a fade point at 'now' with full volume.
	channel->addFadePoint(dspclock + (rate * time), 1.0f);    // Add a fade point 5 seconds later at 0 volume.
}

void MySound::FadeOut(float time)
{
	unsigned long long dspclock;
	SoundManager::ERRCHECK(channel->getDSPClock(0, &dspclock));

	int rate;
	SoundManager::ERRCHECK(SoundManager::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	channel->addFadePoint(dspclock, 1.0f);                 // Add a fade point at 'now' with full volume.
	channel->addFadePoint(dspclock + (rate * time), 0.0f);    // Add a fade point 5 seconds later at 0 volume.
}

void MySound::SetPos(FMOD_VECTOR* pos)
{
	FMOD_VECTOR *vel = nullptr;
	channel->get3DAttributes(nullptr, vel);
	channel->set3DAttributes(pos, vel);
}

void MySound::SetVel(FMOD_VECTOR* vel)
{
	FMOD_VECTOR *pos = nullptr;
	channel->get3DAttributes(pos, nullptr);
	channel->set3DAttributes(pos, vel);
}

void MySound::SetConeOrientarion(FMOD_VECTOR *dir) {
	channel->set3DConeOrientation(dir);

}

void MySound::SetConeSettings(float insideConeAngle,float outsideconeangle, float outsidevolume) {
	channel->set3DConeSettings(insideConeAngle, outsideconeangle, outsidevolume); // angulos en grados

}

void MySound::SetMinMaxDistance(float minDistance, float maxDistance) {
	channel->set3DMinMaxDistance(minDistance, maxDistance);
}

