#pragma once

//#include <GLFW/glfw3.h>
//#include <GL/GLU.h>
#include <math.h>

class Natu {

private:
	float headSize;
	float beakSize;

	float featherSize;
	float wingSize;

	float legSize;
	float footSize;
	float toeSize;

private :
	void drawHead();
	void drawWings();
	void drawTail();
	void drawLeftLeg();
	void drawRightLeg();

public:
	Natu(float headSize, float beakSize, float featherSize, float wingSize, float legSize, float footSize, float toeSize);
	~Natu();

	void drawPokemon();

};