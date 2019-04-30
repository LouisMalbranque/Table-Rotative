#pragma once
#include "arduino.h"
class Peripherique
{
protected:
	int* parameters;

public:
	Peripherique();
	~Peripherique();


	virtual void write(String data) = 0; // méthode abstraite pour l'écriture de données dans le périphérque 
	virtual String read() = 0; // méthode abstrataite pour la lecture depuis le périphérique
	virtual String createDatagramme(int* data) = 0; // méthode abstraite de création de datagramme spécifique pour le périphérique en fonctions des valeurs reçues

};
