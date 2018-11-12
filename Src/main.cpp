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



int main() {
	SoundManager * soundManager = SoundManager::GetInstance();	//Inicializa el motor

	AdriSound * amiguiSound = nullptr;

	std::string path = "../../Media/muestras/piano.ogg";
	amiguiSound = new AdriSound(path.c_str());
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
				amiguiSound->Play();

			else if ((key == 'S') || (key == 's'))
				amiguiSound->Stop();

			else if ((key == 'P') || (key == 'p'))
				amiguiSound->TogglePaused();

			else if ((key == 'Q') || (key == 'q')) break;

			else if ((key == 'Z') || (key == 'z'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave);
			}

			//Re
			else if ((key == 'X') || (key == 'x'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2,(2.0f/12.0f)));
			}

			//Mi
			else if ((key == 'C') || (key == 'c'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2, (4.0f / 12.0f)));
			}

			//Fa
			else if ((key == 'V') || (key == 'v'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2, (5.0f / 12.0f)));
			}

			//Sol
			else if ((key == 'B') || (key == 'b'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2, (7.0f / 12.0f)));
			}

			//La
			else if ((key == 'N') || (key == 'n'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2, (9.0f / 12.0f)));
			}

			//Si
			else if ((key == 'M') || (key == 'm'))
			{
				amiguiSound->Play();
				amiguiSound->SetPitch(currentOctave * pow(2, (11.0f / 12.0f)));
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

		soundManager->Update();
	}

	delete amiguiSound;
	
	SoundManager::ResetInstance();

	return 0;
}
