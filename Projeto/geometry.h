#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <GL/glut.h>
#include <iostream>

// Funções do Robô
void drawCappedCylinderZ(float radius, float height, int slices, int stacks);
void drawBaseWithWheels(float base_x, float base_y, float base_z);
void drawBodyStackedCylinders();

// Funções da Cabeça (para manter a interface limpa, Head() é declarada aqui)
void Head(); 
void loadTexture(const char* filename);

// Funções do Cenário
void drawGround();
void drawCelestialBody();
void drawSceneObjects();

#endif // GEOMETRY_H