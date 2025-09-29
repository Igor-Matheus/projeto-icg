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

void drawBaseWithWheels(float base_x, float base_y, float base_z) {
    glPushMatrix();

    // --- BASE COM TEXTURA ---
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);  // Para a textura não sofrer iluminação
    loadTexture("textura_cabeca.png");
    glBindTexture(GL_TEXTURE_2D, texName);

    glPushMatrix();
        glScalef(base_x, base_y, base_z);

        glBegin(GL_QUADS);
            // Frente
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
            // Trás
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
            // Laterais...
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);

            glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f,  0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f,  0.5f,  0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f,  0.5f, -0.5f);

            // Topo
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.5f, -0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,  0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f,  0.5f);

            // Fundo
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
        glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // --- RODAS ---
    float inner_radius = 0.15f; 
    float outer_radius = 0.45f; 
    float wheel_pos_x = base_x / 2.0f; 
    float wheel_pos_y = 0.0f; 
    float wheel_pos_z = base_z / 2.0f - inner_radius * 2; 

    glColor3f(0.0f, 0.0f, 0.0f); 
    for(int ix=-1; ix<=1; ix+=2){
        for(int iz=-1; iz<=1; iz+=2){
            glPushMatrix();
                glTranslatef(ix*wheel_pos_x, wheel_pos_y, iz*wheel_pos_z);
                glRotatef(90.0f,0,1,0);
                glutSolidTorus(inner_radius, outer_radius, 16,32);
            glPopMatrix();
        }
    }

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

void Head(){
    glPushMatrix();
    // Cor do Material base (branco permite que as texturas mostrem suas cores reais)
    glColor3f(1.0, 1.0, 1.0); 

    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_LIGHTING); // Mantemos a iluminação ativa para todo o corpo da cabeça

    // --- CARREGA E ATIVA A TEXTURA DO CORPO DA CABEÇA ---
    loadTexture("textura_cabeca.png"); 
    glBindTexture(GL_TEXTURE_2D, texName);

    // CAIXA MAIOR (Corpo principal da TV)
    glBegin(GL_QUADS);
        // Lado Esquerdo (X=0)
        glNormal3f(-1.0, 0.0, 0.0); // Normal para fora
        glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.0, 4.0, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.0, 4.0, -2.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 0.0, -2.75);

        // Topo (Y=4.0)
        glNormal3f(0.0, 1.0, 0.0); // Normal para cima
        glTexCoord2f(0.0, 0.0); glVertex3f (6.0, 4.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (6.0, 4.0, -2.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.0, 4.0, -2.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 4.0, 0.0);

        // Lado Direito (X=6.0)
        glNormal3f(1.0, 0.0, 0.0); // Normal para fora
        glTexCoord2f(0.0, 0.0); glVertex3f (6.0, 0.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (6.0, 0.0, -2.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (6.0, 4.0, -2.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (6.0, 4.0, 0.0);

        // Fundo (Y=0.0)
        glNormal3f(0.0, -1.0, 0.0); // Normal para baixo
        glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.0, 0.0, -2.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (6.0, 0.0, -2.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (6.0, 0.0, 0.0);

        // Parte de Trás da Caixa (Z=-2.75)
        glNormal3f(0.0, 0.0, -1.0); // Normal para trás
        glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 4.0, -2.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (6.0, 4.0, -2.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (6.0, 0.0, -2.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 0.0, -2.75);
    glEnd();

    // FRAME DA TELA (PARTE EXTERIOR)
    // Continua usando textura_cabeça.jpg
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0); // Face frontal
        glTexCoord2f(0.0, 0.0); glVertex3f (6.0, 0.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 0.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.5, 0.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 0.0, 0.0);

        glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.5, 0.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.5, 3.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 4.0, 0.0);

        glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 4.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.5, 3.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 3.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (6.0, 4.0, 0.0);

        glTexCoord2f(0.0, 0.0); glVertex3f (6.0, 4.0, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 3.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 0.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (6.0, 0.0, 0.0);
    glEnd();
    
    // FRAME DA TELA (PARTE INTERIOR)
    // Continua usando textura_cabeça.jpg
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0); // Normal para fora (da face)
        glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 0.5, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 0.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 0.5, -0.5); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 0.5, -0.5);

        glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 0.5, -0.5); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.5, 3.5, -0.5); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.5, 3.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 0.5, 0.0);

        glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 3.5, -0.5); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 3.5, -0.5); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 3.5, 0.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 3.5, 0.0);

        glTexCoord2f(0.0, 0.0); glVertex3f (5.5, 0.5, 0.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 3.5, 0.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 3.5, -0.5); 
        glTexCoord2f(0.0, 1.0); glVertex3f (5.5, 0.5, -0.5);
    glEnd();

    // --- TELA (ROSTO) ---
    // Desativa a textura do corpo e carrega a do rosto
    loadTexture("rosto.png"); // Carrega a textura do rosto
    glBindTexture(GL_TEXTURE_2D, texName);
    
    // Para a tela, podemos desativar a iluminação se você quiser um efeito mais "brilhante" (tela emissiva)
    // ou mantê-la ativa se quiser que a luz do ambiente afete a tela.
    // Vou manter a iluminação ativa para que a luz do sol afete.
    // glDisable(GL_LIGHTING); // Removido para a tela ser afetada pela luz
    glColor3f(1.0, 1.0, 1.0); // Cor branca para a textura do rosto aparecer sem matiz
    
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0); // Normal para fora
        glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.5, 0.5, -0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.5, 3.5, -0.5);
        glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 3.5, -0.5);
    glEnd();
    // glEnable(GL_LIGHTING); // Não é necessário reativar se não desativamos

    // --- PARTE DE TRÁS DA TV (O "Cone" Traseiro) ---
    // Reativa a textura do corpo para o cone traseiro
    loadTexture("textura_cabeca.png"); 
    glBindTexture(GL_TEXTURE_2D, texName);
    glColor3f(1.0, 1.0, 1.0); // Cor branca para a textura aparecer sem matiz

    glBegin(GL_QUADS);
        glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 3.75, -2.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.5, 2.75, -4.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.5, 0.5, -4.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 0.1, -2.75);

        glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f (5.5, 0.1, -2.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 0.5, -4.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 2.75, -4.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (5.5, 3.75, -2.75);

        glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f (5.5, 3.75, -2.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 2.75, -4.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (0.5, 2.75, -4.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 3.75, -2.75);

        glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 0.1, -2.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (0.5, 0.5, -4.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 0.5, -4.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (5.5, 0.1, -2.75);

        glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(0.0, 0.0); glVertex3f (0.5, 2.75, -4.75); 
        glTexCoord2f(1.0, 0.0); glVertex3f (5.5, 2.75, -4.75); 
        glTexCoord2f(1.0, 1.0); glVertex3f (5.5, 0.5, -4.75); 
        glTexCoord2f(0.0, 1.0); glVertex3f (0.5, 0.5, -4.75);
    glEnd();

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D); // Desativa a texturização ao sair da função
    // glDisable(GL_LIGHTING); // Se você ativou fora da Head, não desative aqui.
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

void drawArmSegment(float length, float radius, float angle, float x, float y, float z) {
    glPushMatrix();
        // Translação para a posição inicial do segmento
        glTranslatef(x, y, z);
        // Rotação da articulação do segmento
        glRotatef(angle, 0.0, 1.0, 1.0);

        // Cada braço será composto por 3 cilindros menores
        float partLength = length / 3.0f;

        for (int i = 0; i < 3; i++) {
            glPushMatrix();
                // Desloca cada parte ao longo do X (já que o braço se estende nesse eixo)
                glTranslatef(i * partLength, 0.0f, 0.0f);

                // Orienta o cilindro no eixo X
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                // --- MESMA COR DO CORPO ---
                glColor3f(0.75f, 0.75f, 0.75f); // preenchimento

                // Desenha o cilindro curto
                drawCappedCylinderZ(radius, partLength, 16, 4);
            glPopMatrix();
        }
    glPopMatrix();
}

void drawHand(int side) { 
    // Dimensões
    const float WRIST_RADIUS = 0.15f;    
    const float PALM_WIDTH = 0.5f;       
    const float PALM_THICKNESS = 0.3f;   
    const float PALM_LENGTH = 0.8f;      
    const float FINGER_JOINT_SIZE = 0.2f; 
    const float FINGER_WIDTH = 0.1f;    
    const float FINGER_LENGTH = 0.6f;    
    
    // Cores em Tons de Azul
    GLfloat dark_blue_metal[] = {0.1f, 0.2f, 0.4f, 1.0f}; 
    GLfloat bright_blue_metal[] = {0.4f, 0.6f, 1.0f, 1.0f}; 

    // --- 1. Pulso e Palma ---
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bright_blue_metal);
    glPushMatrix();
        glutSolidSphere(WRIST_RADIUS, 16, 16); 
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dark_blue_metal);
    glPushMatrix();
        glTranslatef(WRIST_RADIUS + PALM_LENGTH / 2.0f, 0.0f, 0.0f);
        glScalef(PALM_LENGTH, PALM_WIDTH, PALM_THICKNESS);
        glutSolidCube(1.0);
    glPopMatrix();

    // --- 2. Função Auxiliar para Desenhar um Dedo (Lambda) ---
    // Nota: Mantenha esta lambda function ou a mova para fora se seu compilador não suportar.
    auto drawFinger = [&](float x, float y, float z, float rot_y) {
        
        glPushMatrix();
            glTranslatef(x, y, z);
            glRotatef(rot_y, 0.0f, 1.0f, 0.0f); 

            // Junta Esférica
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bright_blue_metal);
            glutSolidSphere(FINGER_JOINT_SIZE / 2.0f, 8, 8); 

            // Segmento 1
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dark_blue_metal);
            glPushMatrix();
                glTranslatef(FINGER_JOINT_SIZE / 2.0f, 0.0f, 0.0f);
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
                drawCappedCylinderZ(FINGER_WIDTH, FINGER_LENGTH / 2.0f, 8, 2);
            glPopMatrix();

            // Segmento 2 (Meio)
            glPushMatrix();
                glTranslatef(FINGER_JOINT_SIZE / 2.0f + FINGER_LENGTH / 2.0f, 0.0f, 0.0f);
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
                drawCappedCylinderZ(FINGER_WIDTH * 0.8f, FINGER_LENGTH / 2.0f, 8, 2); 
            glPopMatrix();

            // Ponta do Dedo
            glPushMatrix();
                glTranslatef(FINGER_JOINT_SIZE / 2.0f + FINGER_LENGTH, 0.0f, 0.0f);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bright_blue_metal);
                glutSolidSphere(FINGER_WIDTH * 0.8f, 8, 8);
            glPopMatrix();

        glPopMatrix();
    };

    // --- 3. Posições dos Dedos na Palma ---

    float base_x = WRIST_RADIUS + PALM_LENGTH; 
    
    // Dedos (Indicador, Médio, Anelar, Mínimo)
    drawFinger(base_x, PALM_WIDTH * 0.4f, 0.0f, 0.0f); 
    drawFinger(base_x, PALM_WIDTH * 0.1f, 0.0f, 0.0f); 
    drawFinger(base_x, -PALM_WIDTH * 0.2f, 0.0f, 0.0f); 
    drawFinger(base_x * 0.95f, -PALM_WIDTH * 0.4f, 0.0f, 0.0f); 

    // Polegar (CORRIGIDO PARA SIMETRIA)
    glPushMatrix();
        glTranslatef(WRIST_RADIUS * 1.5f, PALM_WIDTH / 2.0f, PALM_THICKNESS / 2.0f); 
        
        // *** CORREÇÃO DO POLEGAR ***
        if (side == -1) {
            // Se for o braço esquerdo, inverte o eixo Y do polegar para que ele 
            // aponte para a frente/corpo, e não para as costas.
            glScalef(1.0f, -1.0f, 1.0f); 
        }
        
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f); 
        drawFinger(0.0f, 0.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Volta ao material padrão (IMPORTANTE)
    GLfloat default_color[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, default_color);
}

void drawRobotArm(int side) { // side = 1 para direito, -1 para esquerdo
    const float ARM_RADIUS = 0.3f;
    const float UPPER_ARM_LENGTH = 2.5f;
    const float FOREARM_LENGTH = 2.5f;

    float shoulder_pivot_y = -2.5f; // altura do ombro abaixo da cabeça
    // Posicionamento corrigido para encostar no corpo
    float shoulder_pivot_x = (-0.3f + ARM_RADIUS) * side + 3.0f; 

    glPushMatrix();
        // 1. Translação para o ombro
        glTranslatef(shoulder_pivot_x, shoulder_pivot_y, -1.5f);
        
        // --- Correção de Orientação e Simetria do Braço ---
        if (side == 1) { // Braço Direito
             // Rotação de 180 em Y para o braço desenhar para dentro (em direção ao corpo)
             glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        } else if (side == -1) { // Braço Esquerdo
            // Espelhamento real (-1.0) e rotação de 180 em Y para a mão ficar orientada para frente.
            glScalef(-1.0f, 1.0f, 1.0f); 
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f); 
        }
        // ----------------------------------------------------

        // Ombro (Segmento Superior)
        glPushMatrix();
            // Controlado pelo teclado (Z/H)
            glRotatef(arm_shoulder_z_angle, 0.0f, 0.0f, 1.0f); 
            drawArmSegment(UPPER_ARM_LENGTH, ARM_RADIUS, 0, 0, 0, 0);

            // Vai até o cotovelo
            glTranslatef(UPPER_ARM_LENGTH, 0.0f, 0.0f);

            // Cotovelo (Segmento Inferior)
            glPushMatrix();
                // Controlado pelo teclado (X/J)
                glRotatef(arm_elbow_z_angle, 0.0f, 0.0f, 1.0f);
                drawArmSegment(FOREARM_LENGTH, ARM_RADIUS, 0, 0, 0, 0);
                
                // Vai até o pulso (ponta do antebraço)
                glTranslatef(FOREARM_LENGTH, 0.0f, 0.0f); 

                // *** ROTAÇÃO DO PULSO PARA VIRAR A MÃO PARA DENTRO ***
                // -90 * side -> Vira as palmas para o corpo em ambos os lados.
                glRotatef(-90.0f * side, 1.0f, 0.0f, 0.0f); 
                
                // *** CHAMADA FINAL DA MÃO ***
                drawHand(side); // <-- PASSA O 'side' PARA CORRIGIR O POLEGAR
                
            glPopMatrix(); 
        glPopMatrix(); 
    glPopMatrix();
}
