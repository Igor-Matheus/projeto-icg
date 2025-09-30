/*
 * robot.c
 * Este arquivo principal agora implementa o controle de movimento GLOBAL do robô
 * no cenário e uma câmera que orbita em torno dele (Terceira Pessoa).
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath> // Para M_PI e funções trigonométricas
#include "geometry.h" 

#define STB_IMAGE_IMPLEMENTATION

// --- Variáveis Globais de Estado ---
static int shoulder = 0, elbow = 0; 

float bodyTilt = 0.0f; 
// NOVO ESTADO DO ROBÔ (Posição Global)
// Recalcula a posição Y para que a base das rodas toque o chão (Y=-12.0)
// Altura do corpo + base (aprox. 10.4). Colocamos a origem Y=0 do robô em Y=-1.6
float robotX = 0.0f; 
float robotY = -1.6f; // VALOR AJUSTADO PARA ATERRAR O ROBÔ
float robotZ = 0.0f; 
float robotAngleY = 0.0f; 
float robotSpeed = 0.5f; 
float robotRotationSpeed = 5.0f; 

// NOVO ESTADO DA CÂMERA (Órbita de Terceira Pessoa)
float camDistance = 20.0f; 
float camOrbitAngle = 0.0f; 
float camHeight = 8.0f;

// AS VARIÁVEIS camX, camY, camZ, camAngleY, walkSpeed FORAM SUBSTITUÍDAS 
// PELA NOVA LÓGICA DE ÓRBITA.

float arm_shoulder_z_angle = -25.0f; // Rotação do ombro (para cima/baixo)
float arm_elbow_z_angle = -25.0f;    // Rotação do cotovelo
// --- FIM das Variáveis Globais ---

// Funções de desenho do arquivo geometry.c são declaradas via geometry.h


void init(void)
{
    // CÉU (Background) e Shading
    glClearColor(0.53, 0.81, 0.98, 0.0); 
    glShadeModel(GL_SMOOTH); 
    glEnable(GL_COLOR_MATERIAL); 
    
    // ILUMINAÇÃO e MATERIAIS
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; 
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_position[] = { 20.0, 30.0, 20.0, 1.0 }; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f); 
    glEnable(GL_LINE_SMOOTH); 
    
    // Configuração de Textura (Mantida)
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 1. CÂMERA DE ÓRBITA (TERCEIRA PESSOA)
    glLoadIdentity();
    
    float totalAngleRad = (robotAngleY + camOrbitAngle) * M_PI / 180.0;
    
    // Ponto de foco: O robô (na altura da cabeça)
    float targetX = robotX;
    float targetZ = robotZ;
    float targetY = robotY + 4.0f; // Foca na altura da cabeça do robô (Y=4.0 da cabeça)

    // Calcula a posição da câmera em órbita
    float camX = targetX + camDistance * sin(totalAngleRad);
    float camY = robotY + camHeight; 
    float camZ = targetZ + camDistance * cos(totalAngleRad);

    gluLookAt(camX, camY, camZ,       // Eye position (Calculada para orbitar)
              targetX, targetY, targetZ,    // Center (Sempre olhando para o robô)
              0.0, 1.0, 0.0);        
    
    // Desenho do Cenário
    drawCelestialBody();
    drawGround();
    drawSceneObjects();
    // 2. TRANSFORMAÇÕES GLOBAIS DO ROBÔ (Movimento e Rotação)
     glPushMatrix();
        // Move o robô para sua posição global no mundo
        glTranslatef(robotX, robotY, robotZ);
        
        // Gira o robô em torno do seu próprio eixo Y (Yaw global)
        glRotatef(robotAngleY, 0.0, 1.0, 0.0);
        
        // Compensação de Geometria: (Mantido)
        glTranslatef(-3.0f, 0.0f, 1.375f); 

        // NOVO: Inclinação do Corpo (ao redor do eixo X).
        // Tudo que vier depois dessa linha será afetado pela inclinação.
        glRotatef(bodyTilt, 1.0, 0.0, 0.0); 
        
        // Rotação de Articulação (Ombro/Cotovelo) - Continua funcionando
        glRotatef((GLfloat)elbow, 0.0, 1.0, 0.0);
        glRotatef((GLfloat)shoulder, 1.0, 0.0, 0.0);

        drawRobotArm(1);  // Braço Direito (side=1)
        drawRobotArm(-1); // Braço Esquerdo (side=-1)

        Head();
        drawBodyStackedCylinders();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0); // Aumentado o far clip
    glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
    // O movimento do robô é calculado com base na sua rotação atual (robotAngleY)
    float rad = robotAngleY * M_PI / 180.0;
    
    // CORREÇÃO: Negamos o coseno para garantir que 0 graus resulte em movimento 
    // para "dentro da tela" (Z negativo), e que a lógica de 180 graus funcione.
    float dirX = sin(rad) * robotSpeed; 
    float dirZ = -cos(rad) * robotSpeed; // <-- CORREÇÃO AQUI
    
    // Velocidade de ajuste dos ângulos do braço
    const float ANGLE_STEP = 5.0f; 
    
    switch (key) {
        // --- CONTROLES DO ROBÔ (Movimento Global) ---
        case 'w': // Mover Frente
        case 'W':
            robotX += dirX;
            robotZ += dirZ;
            break;
            
        case 's': // Mover Trás
        case 'S':
            robotX -= dirX;
            robotZ -= dirZ;
            break;
            
        case 'a': // Girar Esquerda em torno do seu eixo
        case 'A':
            robotAngleY -= robotRotationSpeed;
            break;
            
        case 'd': // Girar Direita em torno do seu eixo
        case 'D':
            robotAngleY += robotRotationSpeed;
            break;
            
        // --- CONTROLES DA CÂMERA (Órbita) ---
        case 'i': // Órbita Esquerda
        case 'I':
            camOrbitAngle -= 5.0f;
            break;
            
        case 'o': // Órbita Direita
        case 'O':
            camOrbitAngle += 5.0f;
            break;

         // --- CONTROLE DE ARTICULAÇÃO (Cotovelo/Cabeça) ---
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // --- CONTROLE DE ARTICULAÇÃO (Cotovelo/Cabeça) - Usaremos X, J para o braço ---
        // Removido o case 'e' / 'E' para usar teclas mais intuitivas para o braço

        // --- NOVO: CONTROLE DO OMBRO (Z/H) ---
        case 'z': // Abaixar o braço (Z é a tecla mais baixa, bom para abaixar)
        case 'Z':
            arm_shoulder_z_angle -= ANGLE_STEP;
            // Limite para baixo (ex: até 90 graus de inclinação)
            if (arm_shoulder_z_angle < -90.0f) arm_shoulder_z_angle = -90.0f;
            break;
            
        case 'h': // Levantar o braço (H é a tecla mais alta, bom para levantar)
        case 'H':
            arm_shoulder_z_angle += ANGLE_STEP;
            // Limite para cima (ex: até 45 graus acima da horizontal)
            if (arm_shoulder_z_angle > 45.0f) arm_shoulder_z_angle = 45.0f;
            break;
            
        // --- NOVO: CONTROLE DO COTOVELO (X/J) ---
        case 'x': // Dobrar o cotovelo (X é próximo do Z, bom para o próximo segmento)
        case 'X':
            arm_elbow_z_angle -= ANGLE_STEP;
            // Limite para dobrar (ex: 150 graus fechado)
            if (arm_elbow_z_angle < -150.0f) arm_elbow_z_angle = -150.0f;
            break;
            
        case 'j': // Esticar o cotovelo (J é próximo do H, bom para esticar)
        case 'J':
            arm_elbow_z_angle += ANGLE_STEP;
            // Limite para esticar (evita que o braço vá para trás)
            if (arm_elbow_z_angle > 0.0f) arm_elbow_z_angle = 0.0f;
            break;

        // --- NOVO: CONTROLE DE INCLINAÇÃO DO CORPO (K/L) ---
        case 'k': // Inclinar para frente (eixo X positivo)
        case 'K':
            if (bodyTilt < 25.0f) bodyTilt += 5.0f; // Limite a 25 graus
            break;
            
        case 'l': // Inclinar para trás (eixo X negativo)
        case 'L':
            if (bodyTilt > -25.0f) bodyTilt -= 5.0f; // Limite a -25 graus
            break;
            
        case 27: exit(0);
        default: break;
    }
    
    // Normaliza o ângulo do robô
    if (robotAngleY > 360.0f) robotAngleY -= 360.0f;
    if (robotAngleY < 0.0f) robotAngleY += 360.0f;
    
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}