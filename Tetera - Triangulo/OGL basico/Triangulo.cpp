#include "Triangulo.h"

Triangulo::Triangulo() {}

void Triangulo::DibujarTriangulos(float x,float y, float z) {
    glPushMatrix();
     glTranslatef(x,y,z); //posicion
    glBegin(GL_TRIANGLES);
        glVertex3f(1.5, 0, 0);
        glVertex3f(0, 2.6, 0);
        glVertex3f(-1.5, 0, 0);
    glEnd();
    glPopMatrix();
}