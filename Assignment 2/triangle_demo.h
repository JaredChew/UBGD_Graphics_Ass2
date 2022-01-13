#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include <windows.h>
#include <math.h>

class TriangleDemo : public DemoBase
{

private:
	float headRotate;
	float wingRotate;

	float upperBeakRotate;
	float lowerBeakRotate;

	float bodyDownTranslate;

	float jumpTranslate;

	float shakeRotate;

public:
	void init()
	{
	}

	void deinit()
	{
	}

	void drawAxis(const Matrix& viewMatrix)
	{
		// ============draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.3f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		glColor3f(0.3f, 1.0f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.3f, 0.3f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		// ============================
	}

	void drawDoughnut(const GLfloat& x, const GLfloat& y, const GLfloat& z,
		const GLfloat& radius, const GLfloat& smoothness,
		const GLfloat& r, const GLfloat& g, const GLfloat& b) {

		GLfloat prevX = 0;
		GLfloat prevZ = 0;

		GLfloat radian = M_PI * 2 / smoothness;

		glBegin(GL_TRIANGLES);

		for (int j = 1; j <= smoothness; j++) {

			float curveX = radius * cos(j * radian);
			float curveY = radius * sin(j * radian);

			for (int i = 0; i < smoothness + 2; i++) {

				float nextX = sin(curveX) * cos(i * radian);
				float nextZ = sin(curveX) * sin(i * radian);

				//Top circle
				//glVertex3f(x, y + radius * sin(j * radian), z);
				//glVertex3f(prevX, y + radius * sin(j * radian), prevZ);
				//glVertex3f(nextX, y + radius * sin(j * radian), nextZ);

				//Bottom circle
				//glVertex3f(x, y + radius * sin((j + 1) * radian), z);
				//glVertex3f(prevX, y + radius * sin((j + 1) * radian), prevZ);
				//glVertex3f(nextX, y + radius * sin((j + 1) * radian), nextZ);

				if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

					glVertex3f(prevX, curveX * sin(j * radian), prevZ);
					glVertex3f(prevX, curveX * sin((j + 1) * radian), prevZ);
					glVertex3f(nextX, curveX * sin((j + 1) * radian), nextZ);

					glVertex3f(prevX, curveX * sin(j * radian), prevZ);
					glVertex3f(nextX, curveX * sin(j * radian), nextZ);
					glVertex3f(nextX, curveX * sin((j + 1) * radian), nextZ);

				}

				prevX = nextX;
				prevZ = nextZ;

			}

		}

		glEnd();

	}

	void drawHeadFeather(const GLfloat& x, const GLfloat& y, const GLfloat& z,
		const GLfloat& radius, const GLfloat& length, const GLfloat& smoothness,
		const GLfloat& r, const GLfloat& g, const GLfloat& b) {

		GLfloat prevX = 0;
		GLfloat prevZ = 0;

		GLfloat radian = M_PI * 2 / smoothness;

		glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for (int i = 0; i <= (smoothness + 1); i++) {

			float nextX = radius * cos(i * radian);
			float nextZ = radius * sin(i * radian) * 2;

			//Top circle
			glVertex3f(x, y, z);
			glVertex3f(x + prevX, y, z + prevZ);
			glVertex3f(x + nextX, y, z + nextZ);

			prevX = nextX;
			prevZ = nextZ;

		}

		glEnd();

	}

	void drawPupil(const GLfloat& x, const GLfloat& y, const GLfloat& z,
		const GLfloat& radius, const GLfloat& smoothness,
		const GLfloat& r, const GLfloat& g, const GLfloat& b) {

		GLfloat prevX = 0;
		GLfloat prevY = 0;

		GLfloat radian = M_PI * 2 / smoothness;

		glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for (int i = 0; i <= (smoothness + 1); i++) {

			float nextX = radius * cos(i * radian);
			float nextY = radius * sin(i * radian);

			glVertex3f(x, y, z);
			glVertex3f(x + prevX, y + prevY, z);
			glVertex3f(x + nextX, y + nextY, z);

			prevX = nextX;
			prevY = nextY;

		}

		glEnd();

	}

	void drawEye(const GLfloat& x, const GLfloat& y, const GLfloat& z,
		const GLfloat& radius, const GLfloat& length, const GLfloat& smoothness,
		const GLfloat& r, const GLfloat& g, const GLfloat& b) {

		GLfloat prevX = 0;
		GLfloat prevY = 0;

		GLfloat radian = M_PI * 2 / smoothness;

		glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for (int i = 0; i <= (smoothness + 1); i++) {

			float nextX = radius * cos(i * radian);
			float nextY = radius * sin(i * radian) * length;

			glVertex3f(x, y, z + (length / 2));
			glVertex3f(x + prevX, y + prevY, z + (length / 2));
			glVertex3f(x + nextX, y + nextY, z + (length / 2));

			prevX = nextX;
			prevY = nextY;

		}

		glEnd();

	}

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

	void drawWingPattern(const GLfloat& x, const GLfloat& y, const GLfloat& z,
		const GLfloat& length, const GLfloat& height,
		const GLfloat& r, const GLfloat g, const GLfloat& b) {

		glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		//z -> x

		glVertex3f(x, y - (height / 2), z - (length / 2));
		glVertex3f(x, y - (height / 2), z + (length / 2));
		glVertex3f(x, y + (height / 2), z - (length / 2));

		glVertex3f(x, y + (height / 2), z - (length / 2));
		glVertex3f(x, y + (height / 2), z + (length / 2));
		glVertex3f(x, y - (height / 2), z + (length / 2));

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

	void head() {

		drawFeather(0.0f, 0.25f, -0.1f, 0.2f, 0.1f, 1.0f, 0.0f, 0.0f); //hair //square
		drawHeadFeather(0.0f, 0.25f, -0.1f, 0.05f, 1.0f, 50.0f, 1.0f, 0.0f, 0.0f); //circle

		drawHead(0.0f, 0.0f, 0.0f, 0.25f, 50.0f, 0.0f, 1.0f, 0.0f); //sphere

		drawBeakUpper(0.0f, 0.025f, 0.25f, 0.1f, 0.05f, 1.0f, 1.0f, 0.0f); //wedge
		drawBeakLower(0.0f, -0.025f, 0.25f, 0.1f, 0.05f, 1.0f, 1.0f, 0.0f); //wedge

		drawEye(-0.1f, 0.07f, 0.11f, 0.05f, 0.25f, 50.0f, 1.0f, 1.0f, 1.0f);
		drawPupil(-0.1f, 0.07f, 0.237f, 0.01f, 50.0f, 0.0f, 0.0f, 0.0f);

		drawEye(0.1f, 0.07f, 0.11f, 0.05f, 0.25f, 50.0f, 1.0f, 1.0f, 1.0f);
		drawPupil(0.1f, 0.07f, 0.237f, 0.01f, 50.0f, 0.1f, 0.1f, 0.1f);

	}

	void leftWing() {

		drawWing(-0.25f, 0.0f, -0.2f, 0.15f, 50.0f, 1.0f, 1.0f, 0.0f); //circle

		drawWing(-0.255f, 0.0f, -0.2f, 0.1f, 50.0f, 0.1f, 0.1f, 0.1f); //wing pattern

		drawWingPattern(-0.257f, -0.05f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square
		drawWingPattern(-0.257f, 0.0f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square
		drawWingPattern(-0.257f, 0.05f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square

	}

	void rightWing() {

		drawWing(0.25f, 0.0f, -0.2f, 0.15f, 50.0f, 1.0f, 1.0f, 0.0f); //circle

		drawWing(0.255f, 0.0f, -0.2f, 0.1f, 50.0f, 0.1f, 0.1f, 0.1f); //wing pattern

		drawWingPattern(0.257f, -0.05f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square
		drawWingPattern(0.257f, 0.0f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square
		drawWingPattern(0.257f, 0.05f, -0.03f, 0.07f, 0.03f, 1.0f, 0.0f, 0.0f); //square

	}

	void tail() {

		drawFeather(-0.06f, -0.13f, -0.25f, 0.3f, 0.1f, 1.0f, 0.0f, 0.0f); //square
		drawFeather(0.0f, -0.15f, -0.25f, 0.3f, 0.1f, 1.0f, 0.0f, 0.0f); //square
		drawFeather(0.06f, -0.13f, -0.25f, 0.3f, 0.1f, 1.0f, 0.0f, 0.0f); //square

	}

	void leftLeg() {

		drawLeg(-0.1f, -0.25f, 0.0f, 0.03f, 0.1f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder

		drawFeet(-0.1f, -0.3f, 0.0f, 0.03f, 0.3f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder

		drawFrontToe(-0.1f, -0.3f, 0.15f, 0.03f, 0.1f, 50.0f, 1.0f, 1.0f, 1.0f); //cone
		drawBackToe(-0.1f, -0.3f, -0.15f, 0.03f, 0.1f, 50.0f, 1.0f, 1.0f, 1.0f); //cone

	}

	void rightLeg() {

		drawLeg(0.1f, -0.25f, 0.0f, 0.03f, 0.1f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder

		drawFeet(0.1f, -0.3f, 0.0f, 0.03f, 0.3f, 50.0f, 1.0f, 0.0f, 0.0f); //cylinder

		drawFrontToe(0.1f, -0.3f, 0.15f, 0.03f, 0.1f, 50.0f, 1.0f, 1.0f, 1.0f); //cone
		drawBackToe(0.1f, -0.3f, -0.15f, 0.03f, 0.1f, 50.0f, 1.0f, 1.0f, 1.0f); //cone

	}

	void peckGround(const Matrix& viewMatrix) {

		leftLeg();
		rightLeg();

		Matrix rotate = Matrix::makeRotateMatrix(headRotate, Vector(1.0f, 0.0f, 0.0f));

		//perform model transformation
		Matrix modelMatrix = rotate;

		//convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		head();
		//rightWing();
		//leftWing();
		tail();

		if (headRotate <= -50.0f) { return; }

		headRotate -= 3.0f;

	}

	void flapWings(const Matrix& viewMatrix) {

		head();
		tail();

		Matrix rotateLeftWing = Matrix::makeRotateMatrix(-wingRotate, Vector(1.0f, 1.0f, 1.0f));
		Matrix rotateRightWing = Matrix::makeRotateMatrix(wingRotate, Vector(1.0f, 1.0f, 1.0f));

		//perform model transformation
		Matrix leftWingModelMatrix = rotateLeftWing;
		Matrix rightWingModelMatrix = rotateRightWing;

		//convert model space to view space
		Matrix leftWingViewSpaceMatrix = viewMatrix * leftWingModelMatrix;
		Matrix rightWingViewSpaceMatrix = viewMatrix * rightWingModelMatrix;

		glLoadMatrixf((GLfloat*)leftWingViewSpaceMatrix.mVal);

		leftWing();

		glLoadMatrixf((GLfloat*)rightWingViewSpaceMatrix.mVal);

		rightWing();

		if (wingRotate <= -30.0f) { return; }

		wingRotate--;

	}

	void openCloseBeak(const Matrix& viewMatrix) {

		Matrix rotateUpperBeak = Matrix::makeRotateMatrix(upperBeakRotate, Vector(1.0f, 0.0f, 0.0f));
		Matrix rotateLowerBeak = Matrix::makeRotateMatrix(-upperBeakRotate, Vector(1.0f, 0.0f, 0.0f));

		//perform model transformation
		Matrix upperBeakModelMatrix = rotateUpperBeak;
		Matrix lowerBeakModelMatrix = rotateLowerBeak;

		//convert model space to view space
		Matrix upperBeakViewSpaceMatrix = viewMatrix * upperBeakModelMatrix;
		Matrix lowerBeakViewSpaceMatrix = viewMatrix * lowerBeakModelMatrix;

		glLoadMatrixf((GLfloat*)upperBeakViewSpaceMatrix.mVal);

		drawBeakUpper(0.0f, 0.025f, 0.25f, 0.1f, 0.05f, 1.0f, 1.0f, 0.0f); //wedge

		glLoadMatrixf((GLfloat*)lowerBeakViewSpaceMatrix.mVal);

		drawBeakLower(0.0f, -0.025f, 0.25f, 0.1f, 0.05f, 1.0f, 1.0f, 0.0f); //wedge

		if (upperBeakRotate <= -10.0f) { return; }

		upperBeakRotate--;

	}

	void bodyDown(const Matrix& viewMatrix) {

		leftLeg();
		rightLeg();

		Matrix translate = Matrix::makeTranslationMatrix(Vector(0.0f, bodyDownTranslate, 0.0f));

		//perform model transformation
		Matrix modelMatrix = translate;

		//convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		head();
		rightWing();
		leftWing();
		tail();

		if (bodyDownTranslate <= -0.03f) { return; }

		bodyDownTranslate -= 0.001f;

	}

	void jumpForward(const Matrix& viewMatrix) {

		Matrix translate = Matrix::makeTranslationMatrix(Vector(0.0f, cos(jumpTranslate), cos(jumpTranslate)));

		//perform model transformation
		Matrix modelMatrix = translate;

		//convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		head();
		rightWing();
		leftWing();
		tail();
		leftLeg();
		rightLeg();

		if (jumpTranslate <= -1.5) { return; }

		jumpTranslate -= 0.01;

	}

	void shake(const Matrix& viewMatrix) {

		leftLeg();
		rightLeg();

		Matrix rotate = Matrix::makeRotateMatrix(shakeRotate, Vector(0.0f, 0.0f, 1.0f));

		//perform model transformation
		Matrix modelMatrix = rotate;

		//convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		head();
		rightWing();
		leftWing();
		tail();

		if (shakeRotate <= -60) { return; }

		shakeRotate--;

	}

	void animationController(const Matrix& viewMatrix) {

		//peckGround(viewMatrix);
		//flapWings(viewMatrix);
		//openCloseBeak(viewMatrix);
		//bodyDown(viewMatrix);
		//jumpForward(viewMatrix);
		shake(viewMatrix);

	}

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);

		glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//enable wireframe mode
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		glColor3f(1.0f, 1.0f, 1.0f);

		//head();
		//wings();
		//tail();
		//legs();
		animationController(viewMatrix);

	}

};

#endif
