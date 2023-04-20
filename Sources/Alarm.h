#pragma once

/**
 * Clase Alarm.
 * 
 * Encargada de manejar los tiempos del juego
 */
class Alarm
{
public:
	int cont;
	bool alarm(int secons);
	Alarm();
};

/**
 * Contructor de la clase alarm.
 * 
 * \param cont
 * 
 */
Alarm::Alarm()
{
	this->cont = 0;
}

/**
 * Funcion alarm.
 * 
 * Encargada de manejar los tempos
 * 
 * \param secons
 * \return 
 */
bool Alarm::alarm(int secons)
{
	if (secons == 0)
	{
		return false;
	}

	if (cont >= secons)
	{
		cont = 0;
		return true;
	}

	cont++;

	return false;
}
