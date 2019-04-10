#pragma once
#include "arduino.h"
class Peripherique
{
protected:
	int* parameters;

public:
	Peripherique();
	~Peripherique();


	virtual void write(String data) = 0;
	virtual String read() = 0;
	virtual void begin() = 0;
	virtual String createDatagramme(int* data) = 0;

};
