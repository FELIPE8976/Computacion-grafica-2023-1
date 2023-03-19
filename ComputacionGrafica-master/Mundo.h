#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería

class Mundo
{
	GLMmodel* objeto;
public:
	Mundo();
	void objetos(char* archivo);
	void objetosSinTextura(float x, float y, float z, float size);
	void objetosTextura(float x, float y, float z, GLuint &textid);
};

