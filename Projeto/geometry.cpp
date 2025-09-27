#define STB_IMAGE_IMPLEMENTATION // ESSA LINHA ATIVA O CÓDIGO DA BIBLIOTECA
#include "geometry.h" // Inclui o cabeçalho criado
#include "stb_image.h" // Precisa estar aqui para que as funções usem
#include <cmath> // Para M_PI, se necessário, mas já está no .c principal

// Variável global de textura (se a Head() precisar dela)
#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

// --- loadTexture (IMPLEMENTAÇÃO) ---
void loadTexture ( const char * filename ) {
    int width , height , nrChannels ;
    unsigned char * data = stbi_load ( filename , & width , & height ,
    & nrChannels , 0);
    if ( data ) {
      glGenTextures (1 , &texName );
      glBindTexture ( GL_TEXTURE_2D , texName );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_LINEAR );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
      if ( nrChannels == 3) {
           gluBuild2DMipmaps ( GL_TEXTURE_2D , GL_RGB , width , height , GL_RGB , GL_UNSIGNED_BYTE , data );
      } else if ( nrChannels == 4) {
           gluBuild2DMipmaps ( GL_TEXTURE_2D , GL_RGBA , width , height , GL_RGBA , GL_UNSIGNED_BYTE , data );
      }
      stbi_image_free ( data );
    } else {
      std :: cerr << " Failed to load texture: " << filename << std :: endl ;
    }
}

// --- drawCappedCylinderZ (IMPLEMENTAÇÃO) ---
void drawCappedCylinderZ(float radius, float height, int slices, int stacks) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);

    // --- 1. MODO SÓLIDO (PREENCHIMENTO) ---
    gluQuadricDrawStyle(q, GLU_FILL);
    gluCylinder(q, radius, radius, height, slices, stacks);

    // Tampas (Sólidas)
    glPushMatrix();
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(q, 0.0, radius, slices, 1); 
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(q, 0.0, radius, slices, 1); 
    glPopMatrix();

    // --- 2. MODO LINHA (CONTORNO das Tampas) ---
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0, -1.0);

    glColor3f(0.0f, 0.0f, 0.0f); 

    gluQuadricDrawStyle(q, GLU_LINE);
    
    GLfloat black_color[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_color);
    
    // Desenha SOMENTE as tampas (contornos)
    glPushMatrix();
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(q, 0.0, radius, slices, 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(q, 0.0, radius, slices, 1);
    glPopMatrix();
    
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    // Volta o material
    GLfloat default_color[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, default_color);
    
    gluDeleteQuadric(q);
}

// --- drawBaseWithWheels (IMPLEMENTAÇÃO) ---
void drawBaseWithWheels(float base_x, float base_y, float base_z) {
    glPushMatrix();

    // Base (Caixa Sólida)
    glColor3f(0.4f, 0.4f, 0.45f); 
    glScalef(base_x, base_y, base_z); 
    glutSolidCube(1.0);
    glScalef(1.0/base_x, 1.0/base_y, 1.0/base_z); 

    // Dimensões da roda
    float inner_radius = 0.15f; 
    float outer_radius = 0.45f; 
    
    // Calcula offsets para posicionar as rodas nas BORDAS da base
    float wheel_pos_x = base_x / 2.0f; 
    float wheel_pos_y = 0.0f;          
    float wheel_pos_z = base_z / 2.0f - inner_radius * 2; 
    
    // Cor da Roda - PRETO (Corrigida para valores RGB válidos 0-1)
    glColor3f(0.0f, 0.0f, 0.0f); 

    // Desenhar as quatro rodas (Toroides em pé)
    glPushMatrix(); glTranslatef(-wheel_pos_x, wheel_pos_y, -wheel_pos_z); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); glutSolidTorus(inner_radius, outer_radius, 16, 32); glPopMatrix();
    glPushMatrix(); glTranslatef(wheel_pos_x, wheel_pos_y, -wheel_pos_z); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); glutSolidTorus(inner_radius, outer_radius, 16, 32); glPopMatrix();
    glPushMatrix(); glTranslatef(-wheel_pos_x, wheel_pos_y, wheel_pos_z); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); glutSolidTorus(inner_radius, outer_radius, 16, 32); glPopMatrix();
    glPushMatrix(); glTranslatef(wheel_pos_x, wheel_pos_y, wheel_pos_z); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); glutSolidTorus(inner_radius, outer_radius, 16, 32); glPopMatrix();

    glPopMatrix();
}

// --- drawBodyStackedCylinders (IMPLEMENTAÇÃO) ---
void drawBodyStackedCylinders() {
    glPushMatrix();
    
    // Dimensões
    const int N = 7;
    const float height = 1.5f;
    const float gap = 0.0f;
    const float body_total_length = N * height; 
    
    // Dimensões da base
    const float radius = 0.6f;
    const float base_x = 2.5f * (radius + 0.8f); 
    const float base_y = 0.8f;                  
    const float base_z = 2.5f * (radius + 0.8f); 

    // 1. Translação Inicial (Centro na Base da Cabeça: Y=0)
    glTranslatef(3.0f, 0.0f, -1.375f); 

    // 2. Desenha o Corpo (Rotacionado) e o Toroide de Junta
    glPushMatrix(); 
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 

        // Desenho dos cilindros
        for (int i = 0; i < N; ++i) {
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -i * (height + gap));
                glColor3f(0.75f, 0.75f, 0.85f);
                drawCappedCylinderZ(radius, height, 32, 4); // Chamada completa
            glPopMatrix();
        }
        
        float junction_z_rot = -((float)(N - 1) * height + gap * (N - 1)); 

        // Toroide (Junta de Acoplamento)
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, junction_z_rot); 
            glColor3f(0.6f, 0.6f, 0.7f); 
            glutSolidTorus(0.15, radius + 0.2, 16, 32); 
        glPopMatrix();

    glPopMatrix(); // Fim do Corpo Rotacionado

    // 3. Base com Rodas - Posicionada no sistema de coordenadas ORIGINAL (Y para cima)
    glPushMatrix();
        
        // Translação em Y para colar a base no toroide com compensação
        glTranslatef(0.0f, -(body_total_length + base_y / 2.0f) + 1.5f, 0.0f);
        
        drawBaseWithWheels(base_x, base_y, base_z);
    glPopMatrix();

    glPopMatrix();
}

// --- Head (IMPLEMENTAÇÃO) ---
void Head(){
    glPushMatrix();
    glColor3f (1.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);

    // CAIXA MAIOR
    glBegin(GL_QUADS);
        glVertex3f (0.0, 0.0, 0.0); glVertex3f (0.0, 4.0, 0.0); glVertex3f (0.0, 4.0, -2.75); glVertex3f (0.0, 0.0, -2.75);
        glVertex3f (6.0, 4.0, 0.0); glVertex3f (6.0, 4.0, -2.75); glVertex3f (0.0, 4.0, -2.75); glVertex3f (0.0, 4.0, 0.0);
        glVertex3f (6.0, 0.0, 0.0); glVertex3f (6.0, 0.0, -2.75); glVertex3f (6.0, 4.0, -2.75); glVertex3f (6.0, 4.0, 0.0);
        glVertex3f (0.0, 0.0, 0.0); glVertex3f (0.0, 0.0, -2.75); glVertex3f (6.0, 0.0, -2.75); glVertex3f (6.0, 0.0, 0.0);
        glVertex3f (0.0, 4.0, -2.75); glVertex3f (6.0, 4.0, -2.75); glVertex3f (6.0, 0.0, -2.75); glVertex3f (0.0, 0.0, -2.75);
    glEnd();

    // FRAME DA TELA (PARTE EXTERIOR)
    glBegin(GL_QUADS);
        glVertex3f (6.0, 0.0, 0.0); glVertex3f (5.5, 0.5, 0.0); glVertex3f (0.5, 0.5, 0.0); glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (0.0, 0.0, 0.0); glVertex3f (0.5, 0.5, 0.0); glVertex3f (0.5, 3.5, 0.0); glVertex3f (0.0, 4.0, 0.0);
        glVertex3f (0.0, 4.0, 0.0); glVertex3f (0.5, 3.5, 0.0); glVertex3f (5.5, 3.5, 0.0); glVertex3f (6.0, 4.0, 0.0);
        glVertex3f (6.0, 4.0, 0.0); glVertex3f (5.5, 3.5, 0.0); glVertex3f (5.5, 0.5, 0.0); glVertex3f (6.0, 0.0, 0.0);
    glEnd();

    // FRAME DA TELA (PARTE INTERIOR)
    glBegin(GL_QUADS);
        glVertex3f (0.5, 0.5, 0.0); glVertex3f (5.5, 0.5, 0.0); glVertex3f (5.5, 0.5, -0.5); glVertex3f (0.5, 0.5, -0.5);
        glVertex3f (0.5, 0.5, -0.5); glVertex3f (0.5, 3.5, -0.5); glVertex3f (0.5, 3.5, 0.0); glVertex3f (0.5, 0.5, 0.0);
        glVertex3f (0.5, 3.5, -0.5); glVertex3f (5.5, 3.5, -0.5); glVertex3f (5.5, 3.5, 0.0); glVertex3f (0.5, 3.5, 0.0);
        glVertex3f (5.5, 0.5, 0.0); glVertex3f (5.5, 3.5, 0.0); glVertex3f (5.5, 3.5, -0.5); glVertex3f (5.5, 0.5, -0.5);
    glEnd();

    // TELA
    glColor3f (1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING); 
    loadTexture("teste.jpg");
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.5, 0.5, -0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.5, 3.5, -0.5);
        glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 3.5, -0.5);
    glEnd();
    glEnable(GL_LIGHTING); 
    glDisable(GL_TEXTURE_2D);

    // PARTE DE TRÁS DA TV
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f (0.5, 3.75, -2.75); glVertex3f (0.5, 2.75, -4.75); glVertex3f (0.5, 0.5, -4.75); glVertex3f (0.5, 0.1, -2.75);
        glVertex3f (5.5, 0.1, -2.75); glVertex3f (5.5, 0.5, -4.75); glVertex3f (5.5, 2.75, -4.75); glVertex3f (5.5, 3.75, -2.75);
        glVertex3f (5.5, 3.75, -2.75); glVertex3f (5.5, 2.75, -4.75); glVertex3f (0.5, 2.75, -4.75); glVertex3f (0.5, 3.75, -2.75);
        glVertex3f (0.5, 0.1, -2.75); glVertex3f (0.5, 0.5, -4.75); glVertex3f (5.5, 0.5, -4.75); glVertex3f (5.5, 0.1, -2.75);
        glVertex3f (0.5, 2.75, -4.75); glVertex3f (5.5, 2.75, -4.75); glVertex3f (5.5, 0.5, -4.75); glVertex3f (0.5, 0.5, -4.75);
    glEnd();

    glDisable(GL_CULL_FACE);
    glPopMatrix();
}

// --- drawCelestialBody (IMPLEMENTAÇÃO) ---
void drawCelestialBody() {
    glPushMatrix();

    // Posiciona o corpo celestial (alinhado com o light0_position)
    glTranslatef(20.0f, 30.0f, 20.0f); 
    
    // Desabilita a iluminação para o Sol parecer auto-iluminado
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.8); // Amarelo pálido
    
    // Desenha uma esfera grande
    glutSolidSphere(5.0, 32, 32); 
    
    glEnable(GL_LIGHTING); // Reabilita a iluminação para o resto da cena

    glPopMatrix();
}

// NOVO: Função para desenhar o chão
void drawGround() {
    glColor3f(0.3f, 0.4f, 0.3f); 

    float ground_y = -12.0f;
    float size = 100.0f; // VALOR AUMENTADO para 100.0f para um chão maior

    glPushMatrix();
        glTranslatef(0.0f, ground_y, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0); 
            
            // O quadrado se estende de -size a +size
            glVertex3f(-size, -size, 0.0f);
            glVertex3f( size, -size, 0.0f);
            glVertex3f( size,  size, 0.0f);
            glVertex3f(-size,  size, 0.0f);
        glEnd();
    glPopMatrix();
}

// Novo: Função para desenhar objetos fixos no mundo
void drawSceneObjects() {
    // 1. Cubo Grande de Referência (Vermelho)
    glPushMatrix();
        glColor3f(0.8f, 0.2f, 0.2f); // Vermelho
        glTranslatef(-15.0f, -8.0f, -15.0f); // Posição fixa no cenário
        glutSolidCube(6.0); // Tamanho
    glPopMatrix();

    // 2. Cubo Médio de Referência (Verde)
    glPushMatrix();
        glColor3f(0.3f, 0.7f, 0.3f); // Verde
        glTranslatef(10.0f, -9.5f, -30.0f); // Posição fixa no cenário
        glutSolidCube(3.0);
    glPopMatrix();

    // 3. Torre de Cilindros (Azul)
    glPushMatrix();
        glColor3f(0.1f, 0.1f, 0.9f); // Azul
        glTranslatef(30.0f, -11.0f, 15.0f); // Posição fixa no cenário
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Gira para ficar em pé
        // Usa a função auxiliar do seu robô
        drawCappedCylinderZ(1.5, 10.0, 16, 4); 
    glPopMatrix();
}