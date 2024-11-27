#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-aug24.h"
#include <iostream>
#include <string>

#define canvas_Width 800
#define canvas_Height 800
#define framerate 60

#define cubeSize 50
#define cubeStart -400

void display_CB()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCallList(1);

  glutSwapBuffers();
}

void timer_CB(int id)
{

}

int main(int argc, char *argv[]) {
  char canvas_Name[] = "Project 5 - Lane Wright";
  glutInit(&argc, argv);
  my_setup(canvas_Width, canvas_Height, canvas_Name);
  gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, cubeStart, 0.0, 1.0, 0.0);
  glGenLists(5);

  // Lighting setup
//   float lightpos[3] = {0.0, 0.0, 0.0};
//   float lightcolor[4] = {0.5, 0.0, 0.0, 1.0};
//   glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
//   glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);

//   float materialcolor[4] = {1.0, 1.0, 1.0, 1.0};
//   glMaterialfv(GL_FRONT, GL_AMBIENT, materialcolor);


    //U
    glNewList(1, GL_COMPILE);
    glPushMatrix();
    //glTranslatef(0.0f, 0.0f, cubeStart);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(cubeSize);
    glPopMatrix();
    glEndList();

    //A
    glNewList(1, GL_COMPILE);

    glEndList();

    //H
    glNewList(1, GL_COMPILE);

    glEndList();


  // Event setup
  glutDisplayFunc(display_CB);
  glutTimerFunc(1000 / framerate, timer_CB, 0);
  glutTimerFunc(1000, timer_CB, 1);
  glutTimerFunc(55, timer_CB, 2);

  glutMainLoop();
  return 0;
}