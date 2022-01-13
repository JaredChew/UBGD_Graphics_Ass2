#include "natu.h"
/*
Natu::Natu(float headSize, float beakSize, float featherSize, float wingSize, float legSize, float footSize, float toeSize) {

	this->headSize = headSize;
	this->beakSize = beakSize;

	this->featherSize = featherSize;
	this->wingSize = wingSize;

	this->legSize = legSize;
	this->footSize = footSize;
	this->toeSize = toeSize;

}

Natu::~Natu() { }

void drawHead(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevCurveX = 0;
	GLfloat prevCurveY = 0;

	GLfloat prevX = 0;
	GLfloat prevZ = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glColor3f(r, g, b);

	glBegin(GL_TRIANGLES);

	for (int i = 1; i <= smoothness; i++) {

		//Curvature of sphere

		float curveX = radius * cos(i * radian);
		float curveY = radius * sin(i * radian);

		for (int j = 1; j <= smoothness; j++) {

			//Triangles to connect into a sphere

			float nextX = sin(curveX) * cos(j * radian);
			float nextZ = sin(curveX) * sin(j * radian);

			//glVertex3f(x, curveY, z);
			//glVertex3f(prevX, curveY, prevZ);
			//glVertex3f(nextX, curveY, nextZ);

			if (i > 1) {
				glVertex3f(prevX, curveY, prevZ);
				glVertex3f(nextX, curveY, nextZ);
				glVertex3f(sin(radius * cos((i - 1) * radian)) * cos(j * radian), prevCurveY, sin(radius * cos((i - 1) * radian)) * sin(j * radian));

				glVertex3f(sin(radius * cos((i - 1) * radian)) * cos(j * radian), prevCurveY, sin(radius * cos((i - 1) * radian)) * sin(j * radian));
				glVertex3f(sin(radius * cos((i - 1) * radian)) * cos((j - 1) * radian), prevCurveY, sin(radius * cos((i - 1) * radian)) * sin((j - 1) * radian));
				glVertex3f(prevX, curveY, prevZ);
			}

			prevX = nextX;
			prevZ = nextZ;

		}

		prevCurveX = curveX;
		prevCurveY = curveY;

	}

	glEnd();

}

void drawLeg(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& height, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevX = 0;
	GLfloat prevZ = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	for (int i = 1; i <= (smoothness + 1); i++) {

		float nextX = radius * cos(i * radian);
		float nextZ = radius * sin(i * radian);

		//Top circle
		glVertex3f(x, y + (height / 2), z);
		glVertex3f(x + prevX, y + (height / 2), z + prevZ);
		glVertex3f(x + nextX, y + (height / 2), z + nextZ);

		//Bottom circle
		glVertex3f(x, y - (height / 2), z);
		glVertex3f(x + prevX, y - (height / 2), z + prevZ);
		glVertex3f(x + nextX, y - (height / 2), z + nextZ);

		//Body of cylinder
		if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

			glVertex3f(x + prevX, y + (height / 2), z + prevZ);
			glVertex3f(x + prevX, y - (height / 2), z + prevZ);
			glVertex3f(x + nextX, y - (height / 2), z + nextZ);

			glVertex3f(x + prevX, y + (height / 2), z + prevZ);
			glVertex3f(x + nextX, y + (height / 2), z + nextZ);
			glVertex3f(x + nextX, y - (height / 2), z + nextZ);

		}

		prevX = nextX;
		prevZ = nextZ;

	}

	glEnd();

}

void drawFeet(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& length, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevX = 0;
	GLfloat prevY = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	for (int i = 0; i <= (smoothness + 1); i++) {

		float nextX = radius * cos(i * radian);
		float nextY = radius * sin(i * radian);

		glVertex3f(x, y, z + (length / 2));
		glVertex3f(x + prevX, y + prevY, z + (length / 2));
		glVertex3f(x + nextX, y + nextY, z + (length / 2));

		glVertex3f(x, y, z - (length / 2));
		glVertex3f(x + prevX, y + prevY, z - (length / 2));
		glVertex3f(x + nextX, y + nextY, z - (length / 2));

		//Body of cylinder
		if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

			glVertex3f(x + prevX, y + prevY, z + (length / 2));
			glVertex3f(x + prevX, y + prevY, z - (length / 2));
			glVertex3f(x + nextX, y + nextY, z - (length / 2));

			glVertex3f(x + prevX, y + prevY, z + (length / 2));
			glVertex3f(x + nextX, y + nextY, z + (length / 2));
			glVertex3f(x + nextX, y + nextY, z - (length / 2));

		}

		prevX = nextX;
		prevY = nextY;

	}

	glEnd();

}

void drawFrontToe(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& length, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevX = 0;
	GLfloat prevY = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	for (int i = 0; i < (smoothness + 1); i++) {

		//z = length

		float nextX = radius * cos(i * radian);
		float nextY = radius * sin(i * radian);

		glVertex3f(x, y, z);
		glVertex3f(x + prevX, y + prevY, z);
		glVertex3f(x + nextX, y + nextY, z);

		if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

			glVertex3f(x + prevX, y + prevY, z);
			glVertex3f(x + nextX, y + nextY, z);
			glVertex3f(x, y, z + (length / 2));

		}

		prevX = nextX;
		prevY = nextY;

	}

	glEnd();

}

void drawBackToe(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& length, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevX = 0;
	GLfloat prevY = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	for (int i = 0; i < (smoothness + 1); i++) {

		//z = length

		float nextX = radius * cos(i * radian);
		float nextY = radius * sin(i * radian);

		glVertex3f(x, y, z);
		glVertex3f(x + prevX, y + prevY, z);
		glVertex3f(x + nextX, y + nextY, z);

		if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

			glVertex3f(x + prevX, y + prevY, z);
			glVertex3f(x + nextX, y + nextY, z);
			glVertex3f(x, y, z - (length / 2));

		}

		prevX = nextX;
		prevY = nextY;

	}

	glEnd();

}

void drawWing(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& radius, const GLfloat& smoothness,
	const GLfloat& r, const GLfloat& g, const GLfloat& b) {

	GLfloat prevY = 0;
	GLfloat prevZ = 0;

	GLfloat radian = M_PI * 2 / smoothness;

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	for (int i = 1; i <= smoothness + 1; i++) {

		float nextZ = radius * cos(i * radian);
		float nextY = radius * sin(i * radian);

		glVertex3f(x, y, z);
		glVertex3f(x, prevY, prevZ);
		glVertex3f(x, nextY, nextZ);

		prevZ = nextZ;
		prevY = nextY;

	}

	glEnd();

}

void drawFeather(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& length, const GLfloat& height,
	const GLfloat& r, const GLfloat g, const GLfloat& b) {

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	glVertex3f(x - (height / 2), y, z - (length / 2));
	glVertex3f(x - (height / 2), y, z + (length / 2));
	glVertex3f(x + (height / 2), y, z - (length / 2));

	glVertex3f(x + (height / 2), y, z - (length / 2));
	glVertex3f(x + (height / 2), y, z + (length / 2));
	glVertex3f(x - (height / 2), y, z + (length / 2));

	glEnd();

}

void drawBeakUpper(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& length, const GLfloat& height,
	const GLfloat& r, const GLfloat g, const GLfloat& b) {

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	//back
	glVertex3f(x - (length / 2), y - (height / 2), z);
	glVertex3f(x + (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y + (height / 2), z);

	glVertex3f(x - (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y - (height / 2), z);

	//top
	glVertex3f(x - (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z);
	glVertex3f(x - (length / 2), y - (height / 2), z + (length / 2) * 2);

	glVertex3f(x - (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y + (height / 2), z);

	//left
	glVertex3f(x - (length / 2), y + (height / 2), z);
	glVertex3f(x - (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x - (length / 2), y - (height / 2), z);

	//right
	glVertex3f(x + (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y - (height / 2), z);

	//bottom
	glVertex3f(x + (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y - (height / 2), z + (length / 2) * 2);

	glVertex3f(x - (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y - (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y - (height / 2), z);

	glEnd();

}

void drawBeakLower(const GLfloat& x, const GLfloat& y, const GLfloat& z,
	const GLfloat& length, const GLfloat& height,
	const GLfloat& r, const GLfloat g, const GLfloat& b) {

	glBegin(GL_TRIANGLES);

	glColor3f(r, g, b);

	//back
	glVertex3f(x - (length / 2), y - (height / 2), z);
	glVertex3f(x + (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y + (height / 2), z);

	glVertex3f(x - (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y - (height / 2), z);

	//top
	glVertex3f(x - (length / 2), y + (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z);
	glVertex3f(x - (length / 2), y + (height / 2), z + (length / 2) * 2);

	glVertex3f(x - (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y + (height / 2), z);

	//left
	glVertex3f(x - (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x - (length / 2), y + (height / 2), z);

	//right
	glVertex3f(x + (length / 2), y - (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y + (height / 2), z);

	//bottom
	glVertex3f(x - (length / 2), y - (height / 2), z);
	glVertex3f(x + (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y + (height / 2), z + (length / 2) * 2);

	glVertex3f(x + (length / 2), y + (height / 2), z + (length / 2) * 2);
	glVertex3f(x + (length / 2), y - (height / 2), z);
	glVertex3f(x - (length / 2), y - (height / 2), z);

	glEnd();

}

void Natu::drawHead(){

		drawHead(0, 0, 0, 0.25f, 50, 0, 1, 0); //sphere
		drawBeakUpper(0, 0.025, 0.25, 0.1, 0.05, 1, 1, 0); //wedge
		drawBeakLower(0, -0.025, 0.25, 0.1, 0.05, 1, 1, 0); //wedge
		drawFeather(0, 0.25, -0.1, 0.2, 0.1, 1, 0, 0); //hair //square
		//eyes

}

void Natu::drawWings(){

		drawWing(-0.25, 0, -0.2, 0.15, 50, 1, 1, 0); //circle
		drawWing(0.25, 0, -0.2, 0.15, 50, 1, 1, 0); //circle
		//wing pattern

}

void Natu::drawTail(){

		drawFeather(-0.06, -0.13, -0.25, 0.3, 0.1, 1, 0, 0); //square
		drawFeather(0, -0.15, -0.25, 0.3, 0.1, 1, 0, 0); //square
		drawFeather(0.06, -0.13, -0.25, 0.3, 0.1, 1, 0, 0); //square

}

void Natu::drawLeftLeg(){

		drawLeg(0.1f, -0.25f, 0.0f, 0.03f, 0.1f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder
		drawFeet(0.1, -0.3, 0, 0.03, 0.3, 50, 1, 0, 0); //cylinder
		drawFrontToe(0.1, -0.3, 0.15, 0.03, 0.1, 50, 1, 1, 1); //cone
		drawBackToe(0.1, -0.3, -0.15, 0.03, 0.1, 50, 1, 1, 1); //cone

}

void Natu::drawRightLeg(){

		drawLeg(-0.1f, -0.25f, 0.0f, 0.03f, 0.1f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder
		drawFeet(-0.1, -0.3, 0, 0.03, 0.3, 50, 1, 0, 0); //cylinder
		drawFrontToe(-0.1, -0.3, 0.15, 0.03, 0.1, 50, 1, 1, 1); //cone
		drawBackToe(-0.1, -0.3, -0.15, 0.03, 0.1, 50, 1, 1, 1); //cone

}

void Natu::drawPokemon() {

	drawHead();
	drawWings();
	drawTail();
	drawLeftLeg();
	drawRightLeg();

}

*/