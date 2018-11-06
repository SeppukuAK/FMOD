#include <stdlib.h>
#include <iostream>
#include "fmod.hpp" // para utilizar el wrapper C++
#include "fmod_errors.h" // para manejo de errores


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

int main() {
	//Inicialización básica
	System *system;
	FMOD_RESULT result;
	result = System_Create(&system); // Creamos el objeto system
	ERRCHECK(result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = system->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD
	ERRCHECK(result);

	//Carga de un sonido
	Sound *sound1 = nullptr;
	result = system->createSound(
		"../../Media/muestras/piano.ogg", // path al archivo de sonido
		FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&sound1); // handle al buffer de sonido

	//Asignación de sonido a un canal
	Channel *channel = nullptr;
	result = system->playSound(
		sound1, // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca sin "pause" (se reproduce directamente)
		&channel); // devuelve el canal que asigna
		// el sonido ya se esta reproduciendo

	result = channel->setVolume(0.7f);

	while (true)
		result = system->update();


	//Cierra el sistema
	result = system->release();
	ERRCHECK(result);

	return 0;
}

