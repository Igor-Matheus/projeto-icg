/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * robot.c
 * This program shows how to composite modeling transformations
 * to draw translated and rotated hierarchical models.
 * Interaction:  pressing the s and e keys (shoulder and elbow)
 * alters the rotation of the robot arm.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static int shoulder = 0, elbow = 0;

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void loadTexture ( const char * filename ) {
   int width , height , nrChannels ;
   unsigned char * data = stbi_load ( filename , & width , & height ,
   & nrChannels , 0);
   if ( data ) {
      glGenTextures (1 , &texName );
      glBindTexture ( GL_TEXTURE_2D , texName );
      // Set texture wrapping and filtering parameters
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S ,
      GL_REPEAT );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T ,
      GL_REPEAT );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER ,
      GL_LINEAR_MIPMAP_LINEAR );
      glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER ,
      GL_LINEAR );
      // Load the texture data ( check if it 's RGB or RGBA )
      if ( nrChannels == 3) {
         gluBuild2DMipmaps ( GL_TEXTURE_2D , GL_RGB , width ,
         height , GL_RGB , GL_UNSIGNED_BYTE , data );
      } else if ( nrChannels == 4) {
         gluBuild2DMipmaps ( GL_TEXTURE_2D , GL_RGBA , width ,
         height , GL_RGBA , GL_UNSIGNED_BYTE , data );
      }
      stbi_image_free ( data );
   } else {
      std :: cerr << " Failed ␣to␣ load ␣ texture :␣" << filename <<
      std :: endl ;
   }
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);

   // Propriedades do material
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   // Propriedades da luz
   GLfloat light0_ambient[] = { 0.0, 0.3, 0.0, 1.0 };
   GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light0_position[] = { 1.0, 10.0, 1.0, 1.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   //Parâmetros de textura
   #ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Head(){
   glPushMatrix();

   glRotatef(elbow, 0, 1, 0);
   glRotatef(shoulder, 1, 0, 0);

   glColor3f (1.0, 1.0, 1.0);

   glEnable(GL_CULL_FACE);

   //CAIXA MAIOR
   glBegin(GL_QUADS);   
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.0, 4.0, 0.0);
      glVertex3f (0.0, 4.0, -2.75);
      glVertex3f (0.0, 0.0, -2.75);

      glVertex3f (6.0, 4.0, 0.0);
      glVertex3f (6.0, 4.0, -2.75);
      glVertex3f (0.0, 4.0, -2.75);
      glVertex3f (0.0, 4.0, 0.0);

      glVertex3f (6.0, 0.0, 0.0);
      glVertex3f (6.0, 0.0, -2.75);
      glVertex3f (6.0, 4.0, -2.75);
      glVertex3f (6.0, 4.0, 0.0);

      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, -2.75);
      glVertex3f (6.0, 0.0, -2.75);
      glVertex3f (6.0, 0.0, 0.0);
      
      glVertex3f (0.0, 4.0, -2.75);
      glVertex3f (6.0, 4.0, -2.75);
      glVertex3f (6.0, 0.0, -2.75);
      glVertex3f (0.0, 0.0, -2.75); 
   glEnd();

   //FRAME DA TELA (PARTE EXTERIOR)
   glBegin(GL_QUADS);
      glVertex3f (6.0, 0.0, 0.0);
      glVertex3f (5.5, 0.5, 0.0);
      glVertex3f (0.5, 0.5, 0.0);
      glVertex3f (0.0, 0.0, 0.0);

      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.5, 0.5, 0.0);
      glVertex3f (0.5, 3.5, 0.0);
      glVertex3f (0.0, 4.0, 0.0);

      glVertex3f (0.0, 4.0, 0.0);
      glVertex3f (0.5, 3.5, 0.0);
      glVertex3f (5.5, 3.5, 0.0);
      glVertex3f (6.0, 4.0, 0.0);
      
      glVertex3f (6.0, 4.0, 0.0);
      glVertex3f (5.5, 3.5, 0.0);
      glVertex3f (5.5, 0.5, 0.0);
      glVertex3f (6.0, 0.0, 0.0); 
   glEnd();

   //FRAME DA TELA (PARTE INTERIOR)
   glBegin(GL_QUADS);
      glVertex3f (0.5, 0.5, 0.0);
      glVertex3f (5.5, 0.5, 0.0);
      glVertex3f (5.5, 0.5, -0.5);
      glVertex3f (0.5, 0.5, -0.5);
      
      glVertex3f (0.5, 0.5, -0.5);
      glVertex3f (0.5, 3.5, -0.5);
      glVertex3f (0.5, 3.5, 0.0);
      glVertex3f (0.5, 0.5, 0.0);

      glVertex3f (0.5, 3.5, -0.5);
      glVertex3f (5.5, 3.5, -0.5);
      glVertex3f (5.5, 3.5, 0.0);
      glVertex3f (0.5, 3.5, 0.0);

      glVertex3f (5.5, 0.5, 0.0);
      glVertex3f (5.5, 3.5, 0.0);
      glVertex3f (5.5, 3.5, -0.5);
      glVertex3f (5.5, 0.5, -0.5);
   glEnd();

   //TELA
   glColor3f (1, 1, 1);
   glEnable(GL_TEXTURE_2D);
   loadTexture("teste.jpg");
   glBindTexture(GL_TEXTURE_2D, texName);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
      glTexCoord2f(1.0, 1.0); glVertex3f(5.5, 0.5, -0.5);
      glTexCoord2f(1.0, 0.0); glVertex3f(5.5, 3.5, -0.5);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 3.5, -0.5);
   glEnd();
   glDisable(GL_TEXTURE_2D);


   //PARTE DE TRÁS DA TV
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_QUADS);
      glVertex3f (0.5, 3.75, -2.75);
      glVertex3f (0.5, 2.75, -4.75);
      glVertex3f (0.5, 0.5, -4.75);
      glVertex3f (0.5, 0.1, -2.75);

      glVertex3f (5.5, 0.1, -2.75);
      glVertex3f (5.5, 0.5, -4.75);
      glVertex3f (5.5, 2.75, -4.75);
      glVertex3f (5.5, 3.75, -2.75);

      glVertex3f (5.5, 3.75, -2.75);
      glVertex3f (5.5, 2.75, -4.75);
      glVertex3f (0.5, 2.75, -4.75);
      glVertex3f (0.5, 3.75, -2.75);

      glVertex3f (0.5, 0.1, -2.75);
      glVertex3f (0.5, 0.5, -4.75);
      glVertex3f (5.5, 0.5, -4.75);
      glVertex3f (5.5, 0.1, -2.75);

      glVertex3f (0.5, 2.75, -4.75);
      glVertex3f (5.5, 2.75, -4.75);
      glVertex3f (5.5, 0.5, -4.75);
      glVertex3f (0.5, 0.5, -4.75);
   glEnd();

   glDisable(GL_CULL_FACE);

   glPopMatrix();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();

   Head();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (-1.0, -2.0, -15.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
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
