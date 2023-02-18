#include "Cola.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#define ANGULO 45

//Cola::Cola(){}

void Cola::DibujarCola(float angulo,int n,float x, float y, float z) {
	glPushMatrix();
		glTranslatef(x, y, z);

		glPushMatrix();
		glTranslatef(-0.25, 0.0, 0.0);
		glRotatef(angulo,0.0, 0.0, 1.0);
		glTranslatef(0.25, 0.0, 0.0);
		glPushMatrix();
		glScalef(0.5, 0.4, 1.0);
		glutSolidCube(1.0);
		glPopMatrix();

		for (int i = 0; i < n; i++) {
			glTranslatef(0.25, 0.0, 0.0);
			glRotatef(angulo, 0.0, 0.0, 1.0);
			glTranslatef(0.50, 0.0, 0.0);
			glPushMatrix();
			glScalef(0.5, 0.4, 1.0);
			glutSolidCube(1.0);
			glPopMatrix();
		};
		glPopMatrix();
	glPopMatrix();
};