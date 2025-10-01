#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>

extern float arm_shoulder_z_angle;
extern float arm_shoulder_y_angle;
extern float arm_elbow_z_angle;

// Lista de texturas possíveis para o rosto
extern std::vector<std::string> faceTextures;

extern int currentFaceIndex;

extern bool currentIlumination;

// Funções do Robô
void drawCappedCylinderZ(float radius, float height, int slices, int stacks);
void drawBaseWithWheels(float base_x, float base_y, float base_z);
void drawBodyStackedCylinders(float bodyTilt, int baseTilt);
void drawArmSegment(float length, float radius, float angle, float x, float y, float z);
void drawRobotArm(int side);
void drawHand(int side);

// Funções da Cabeça (para manter a interface limpa, Head() é declarada aqui)
void Head(); 
void loadTexture(const char* filename);

// Funções do Cenário
void applyLighting();
void drawGround();
void drawCelestialBody();
void drawSceneObjects();
void drawSeaweed(float x, float z);
void drawRock(float x, float z);
void drawBubble(float x, float y, float z);
void drawSceneElements();

// Função para configurar iluminação estilo fundo do mar
void setupLighting();

#endif // GEOMETRY_H