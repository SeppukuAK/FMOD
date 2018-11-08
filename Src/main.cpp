#include <conio.h>
#include "Sound.h"
#include "SoundManager.h"
#include <string>

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

	bool paused; float volume = 1.0;
	while (true) {
		if (_kbhit())
		{
			int key = _getche();
			if ((key == 'P') || (key == 'p'))
				amiguiSound->TogglePaused();

			else if (key == 'V')
			{
				if (volume < 1.0)
				{
					volume = volume + 0.1;
					amiguiSound->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}
			else if (key == 'v')
			{
				if (volume > 0) {
					volume = volume - 0.1;
					amiguiSound->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}

			else if ((key == 'Q') || (key == 'q')) break;
		}

	}

	delete amiguiSound;
	
	SoundManager::ResetInstance();

	return 0;
}

