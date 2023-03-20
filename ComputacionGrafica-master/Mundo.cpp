// Esta es la clase que contiene las funciones para el llamado de los objetos a utilizar, tanto con textura como sin textura

#include "Mundo.h"

Mundo::Mundo(){}

// Función encargada de llamar el archivo .obj del objeto a usar
void Mundo::objetos(char* archivo) {
	
	objeto = NULL;
	
	if (!objeto)
	{
		objeto = glmReadOBJ(archivo);
		if (!objeto)
			exit(0);
		glmUnitize(objeto);
		glmFacetNormals(objeto);
		glmVertexNormals(objeto, 90.0);
	}
}


// Función encargada de posicionar y dimensionar objetos sin textura en el mundo
void Mundo::objetosSinTextura(float x, float y, float z, float size) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glmDraw(objeto, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}


// Función encargada de posicionar objetos con la textura deseada en el mundo
void Mundo::objetosTextura(float x, float y, float z, GLuint &texid) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, texid);
	glmDraw(objeto, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}
