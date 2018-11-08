#include <stdlib.h>
#include <iostream>
#include "fmod.hpp" // para utilizar el wrapper C++
#include "fmod_errors.h" // para manejo de errores
#include <conio.h>


/*
C\software\FMOD\API\LOWLEVEL
\DOC

dll y lib necesita
64 dll y 64.lib

*/

using namespace FMOD;

//Facilita la gestión de errores
void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		//printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

//Método para pausa o despausar el audio
void TogglePaused(FMOD::Channel* channel) {
	bool paused;
	channel->getPaused(&paused);
	channel->setPaused(!paused);
}

int main() {

	//Inicialización básica
	System *system;
	FMOD_RESULT result = System_Create(&system); ERRCHECK(result);// Creamos el objeto system

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = system->init(128, FMOD_INIT_NORMAL, 0); ERRCHECK(result);// Inicializacion de FMOD


	//Carga de un sonido
	Sound *sound1 = nullptr;

	result = system->createSound(
		"../../Media/muestras/piano.ogg",
		FMOD_DEFAULT | FMOD_LOOP_NORMAL, // valores (por defecto: sin loop, 2D) Existen más alternativas
		0, // informacion adicional (nada en este caso)
		&sound1);


	//Asignación de sonido a un canal
	Channel *channel = nullptr; //Hereda de ChannelControl(param de los canales)

	//Clases adicionales
	//Posibles clases adicionales
	//ChannelGroup --> canal virtual para agrupar varios canales
	//DSP--> filtros, mezclas, reber
	//Geometry --> simulación de recintos acústicos
	//Reber3D //Clases adicionales

	//Reproducción del sonido
	result = system->playSound(
		sound1,
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		true, // arranca con "pause" 
		&channel);


	//Modificación volumen
	result = channel->setVolume(0.7f);

	//Posiciona en el tiempo 
	channel->setPosition(0, FMOD_TIMEUNIT_MS); //Medio segundo después

	// se repite indefinidamente
	channel->setLoopCount(-1);
	// Se repite una sola vez
	//channel->setLoopCount(0);
	// Tres veces
	//channel->setLoopCount(2);

	//channel->setMute(true); Silencia/activa el canal.

	//Modifica el volumen de sonidos multicanal. Por ejemplo en un sonido estéreo
	//channel->setMixLevelsOutput(frontleft, frontright, center, ..., backleft, backright);
	//channel->setPicth(2.0f);
	//channel->setFrequency(rateHz);

	TogglePaused(channel);

	//Bucle principal
	printf("[P] Pausar/Despausar\n[V/v] Subir/bajar volumen\n[Q] Salir\n");

	bool paused; float volume = 1.0;
	while (true) {
		if (_kbhit())
		{
			int key = _getche();
			if ((key == 'P') || (key == 'p'))
			{
				result = channel->getPaused(&paused); ERRCHECK(result);
				result = channel->setPaused(!paused); ERRCHECK(result);
			}
			else if (key == 'V')
			{
				if (volume < 1.0)
				{
					volume = volume + 0.1;
					result = channel->setVolume(volume); ERRCHECK(result);
					printf("Volume: %f\n", volume);
				}
			}
			else if (key == 'v')
			{
				if (volume > 0) {
					volume = volume - 0.1;
					result = channel->setVolume(volume); ERRCHECK(result);
					printf("Volume: %f\n", volume);
				}
			}
			else if ((key == 'Q') || (key == 'q')) break;

		}		result = system->update();
	}

	//Libera el buffer de sonido
	result = sound1->release(); ERRCHECK(result);

	//Cierra el sistema
	result = system->release(); ERRCHECK(result); //Libera el sonido


	return 0;
}

