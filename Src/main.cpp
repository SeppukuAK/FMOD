#include <conio.h>
#include "Sound.h"
#include "SoundManager.h"
#include <string>
#include <math.h>       /* pow */

/*
C\software\FMOD\API\LOWLEVEL
\DOC

dll y lib necesita
64 dll y 64.lib

*/


void Ejercicio1()
{
	MySound * footstepSound = nullptr;

	std::string path = "../../Media/muestras/piano.ogg";
	footstepSound = new MySound(path.c_str(), FMOD_2D | FMOD_LOOP_NORMAL);
	//Bucle principal

	printf("[P] Pausar/Despausar\n[V/v] Subir/bajar volumen\n[Q] Salir\n");

	bool paused;
	float volume = 1.0;
	float currentOctave = 1.0f;
	while (true)
	{
		if (_kbhit())
		{
			int key = _getche();

			if ((key == 'W') || (key == 'w'))
				footstepSound->Play();

			else if ((key == 'S') || (key == 's'))
				footstepSound->Stop();

			else if ((key == 'P') || (key == 'p'))
				footstepSound->TogglePaused();

			else if ((key == 'Q') || (key == 'q')) break;

			//Do
			else if ((key == 'Z') || (key == 'z'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave);
			}

			//Re
			else if ((key == 'X') || (key == 'x'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (2.0f / 12.0f)));
			}

			//Mi
			else if ((key == 'C') || (key == 'c'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (4.0f / 12.0f)));
			}

			//Fa
			else if ((key == 'V') || (key == 'v'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (5.0f / 12.0f)));
			}

			//Sol
			else if ((key == 'B') || (key == 'b'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (7.0f / 12.0f)));
			}

			//La
			else if ((key == 'N') || (key == 'n'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (9.0f / 12.0f)));
			}

			//Si
			else if ((key == 'M') || (key == 'm'))
			{
				footstepSound->Play();
				footstepSound->SetPitch(currentOctave * pow(2, (11.0f / 12.0f)));
			}
			//+
			else if (key == ',')
			{
				currentOctave *= 2;
			}

			//-
			else if (key == '.')
			{
				currentOctave /= 2;
			}

		}

		SoundManager::GetInstance()->Update();
	}

	delete footstepSound;

}

void Ejercicio2()
{
	SoundManager * soundManager = SoundManager::GetInstance();

	soundManager->GetSystem()->set3DNumListeners(1);

	FMOD_VECTOR listenerPos;
	listenerPos.x = 15;
	listenerPos.y = 0;
	listenerPos.z = 15;
	soundManager->SetListenerPos(&listenerPos);

	MySound * footstepSound = nullptr;
	std::string path = "../../Media/muestras/footstep.wav";
	footstepSound = new MySound(path.c_str(), FMOD_3D | FMOD_LOOP_NORMAL);
	footstepSound->Play();

	footstepSound->SetLoop(true);
	FMOD_VECTOR sourcePos;
	sourcePos.x = 15;
	sourcePos.y = 0;
	sourcePos.z = 5;
	footstepSound->SetPos(&sourcePos);

	FMOD_VECTOR dir = { 1.0f, 2.0f, 3.0f };
	footstepSound->SetConeOrientarion(&dir);

	footstepSound->SetConeSettings(30.0f, 60.0f, 0.5f); // angulos en grados

	//Para calcular la velocidad de una fuente de sonido utilizamos la posicion de la entidad
	//vel.x = (pos.x - lastPos.x) * elapsed;


	while (true)
	{
		if (_kbhit())
		{
			int key = _getche();
			if ((key == 'Q') || (key == 'q')) break;

			if ((key == 'W') || (key == 'w'))
			{
				listenerPos.z += 1;
				soundManager->SetListenerPos(&listenerPos);
			}

			if ((key == 'S') || (key == 's'))
			{
				listenerPos.z -= 1;
				soundManager->SetListenerPos(&listenerPos);
			}

			if ((key == 'A') || (key == 'a'))
			{
				listenerPos.x -= 1;
				soundManager->SetListenerPos(&listenerPos);
			}

			if ((key == 'D') || (key == 'd'))
			{
				listenerPos.x += 1;
				soundManager->SetListenerPos(&listenerPos);
			}

			if ((key == 'J') || (key == 'j'))
			{

				sourcePos.x -= 1;
				footstepSound->SetPos(&sourcePos);

			}

			if ((key == 'K') || (key == 'k'))
			{
				sourcePos.z -= 1;
				footstepSound->SetPos(&sourcePos);
			}

			if ((key == 'L') || (key == 'l'))
			{
				sourcePos.x += 1;
				footstepSound->SetPos(&sourcePos);
			}
			if ((key == 'I') || (key == 'i'))
			{
				sourcePos.z += 1;
				footstepSound->SetPos(&sourcePos);
			}
			//if ((key == 'Y') || (key == 'y'))
			//{
			//	footstepSound->SetConeOrientarion();
			//}
		}

		SoundManager::GetInstance()->Update();
	}

	/*
	Buscar goto(x,y)
	*/
	delete footstepSound;
}

//TODO: ChannelGroup
//Se pueden crear grupos de canales y crear jerarquias
void ChannelGroup()
{
	//	// creamos un grupo de canales ``channelGroup''
	//	FMOD::ChannelGroup* channelGroup;
	//	system->createChannelGroup("grupo1", &channelGroup);
	//
	//	// aniadimos un canal existente, channel, al grupo
	//	channel->setChannelGroup(channelGroup);
	//	// se puede anidir un canal a un grupo directamente con
	//	// playSound(...,group,...,...) mas eficiente!
	//
	//	// aniadimos este grupo como hijo de otro grupo ``anotherGroup''
	//	channelGroup->addGroup(anotherGroup);
	//
	//	// hay un ``master'' (raiz del arbol de grupos) que se puede acceder asi:
	//	ChannelGroup* masterGroup;
	//	system->getMasterChannelGroup(&masterGroup);
	//
	//
	//	// Parar todos los canales del grupo
	//	channelGroup->stop();
	//	// Silenciar, pausar
	//	channelGroup->setMute(true);
	//	channelGroup->setPaused(true);
	//	// ajustar volumen
	//	channelGroup->setVolume(0.5f);
	//	// duplicar pitch
	//	channelGroup->setPitch(2.0f);
}

int main() {
	SoundManager * soundManager = SoundManager::GetInstance();	//Inicializa el motor

	FMOD_VECTOR
		listenerPos = { 0,0,0 }, // posicion del listener
		listenerVel = { 0,0,0 }, // velocidad del listener
		up = { 0,1,0 }, // vector up: hacia la ``coronilla''
		at = { 1,0,0 }; // vector at: hacia donde mira

	//colocamos listener
	soundManager->SetListener(0, &listenerPos, &listenerVel, &up, &at);

	Ejercicio1();

	//Ejercicio2();

	SoundManager::ResetInstance();

	return 0;
}
