#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <GL/glut.h>
#include <iostream>

extern float arm_shoulder_z_angle;
extern float arm_elbow_z_angle;

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

void drawArmSegment(float length, float radius, float angle, float x, float y, float z);
void drawRobotArm(int side);
void drawHand(); // Adicione este
#endif // GEOMETRY_H