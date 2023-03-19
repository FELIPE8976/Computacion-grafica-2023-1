#include "Mundo.h"

Mundo::Mundo(){}

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

void Mundo::objetosSinTextura(float x, float y, float z, float size) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glmDraw(objeto, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

void Mundo::objetosTextura(float x, float y, float z, GLuint &texid) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, texid);
	glmDraw(objeto, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}
