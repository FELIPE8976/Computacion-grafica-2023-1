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
