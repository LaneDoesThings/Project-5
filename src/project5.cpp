#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-aug24.h"
#include <iostream>
#include <string>

#define canvas_Width 800
#define canvas_Height 800
#define framerate 60

#define cubeSize 50.0
#define cubeStart -400.0
#define groundPlane -200.0

struct vec3
{
  double x;
  double y;
  double z;
};

void display_CB()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glCallList(1);
  glCallList(2);
  glCallList(3);

  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3i(0.0, -300.0, cubeStart);
  glVertex3i(0.0, 500.0, cubeStart);
  glEnd();
  glPopMatrix();

  glutSwapBuffers();
}

void timer_CB(int id)
{
  // Framerate
  if (id == 0) {
    glutTimerFunc(1000 / framerate, timer_CB, 0);
    glutPostRedisplay();
  }
}

int main(int argc, char *argv[]) {
  char canvas_Name[] = "Project 5 - Lane Wright";
  glutInit(&argc, argv);
  my_setup(canvas_Width, canvas_Height, canvas_Name);
  glGenLists(5);

  // Lighting setup
  float lightpos[3] = {0.0, 0.0, 0.0};
  float lightcolor[4] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);

  float materialcolor[4] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialcolor);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  struct vec3 uPos = {.x = (-cubeSize * 6) - (cubeSize / 2), .y = groundPlane + (cubeSize * 2), .z = cubeStart};
  struct vec3 aPos = {.x = (-cubeSize) - (cubeSize / 2), .y = groundPlane, .z = cubeStart};
  struct vec3 hPos = {.x = (cubeSize * 4) - (cubeSize / 2), .y = groundPlane + (cubeSize * 2), .z = cubeStart};

    //U
    glNewList(1, GL_COMPILE);
    for(int i = 0; i < 4; i++)
    {
      glPushMatrix();
      glTranslatef(uPos.x, uPos.y - cubeSize * i, uPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }
    for(int i = 1; i < 4; i++)
    {
      glPushMatrix();
      glTranslatef(uPos.x + cubeSize * i, uPos.y - cubeSize * 3, uPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }

    for(int i = 0; i < 3; i++)
    {
      glPushMatrix();
      glTranslatef(uPos.x + cubeSize * 3, uPos.y - cubeSize * i, uPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }
    glEndList();

    //A
    glNewList(2, GL_COMPILE);

    for(int i = 0; i < 4; i++)
    {
      glPushMatrix();
      glTranslatef(aPos.x + cubeSize * i, aPos.y, aPos.z);
      glutWireCube(cubeSize);
      glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(aPos.x - (cubeSize / 2), aPos.y - cubeSize, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + (cubeSize / 2), aPos.y + cubeSize, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + cubeSize, aPos.y + cubeSize * 2, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + cubeSize * 2, aPos.y + cubeSize * 2, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + cubeSize * 2 + (cubeSize / 2), aPos.y + cubeSize, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + cubeSize * 3 + (cubeSize / 2), aPos.y - cubeSize, aPos.z);
    glutWireCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aPos.x + cubeSize + (cubeSize / 2.0), aPos.y + cubeSize, aPos.z);
    glutSolidSphere(cubeSize / 2.0, 25, 10);
    glPopMatrix();

    glBegin(GL_TRIANGLES);
    glVertex3f(aPos.x + cubeSize, aPos.y + cubeSize * 2 + (cubeSize / 2.0), aPos.z);
    glVertex3f(aPos.x + cubeSize * 2, aPos.y + cubeSize * 2 + (cubeSize / 2.0), aPos.z);
    glVertex3f((aPos.x + cubeSize) + (cubeSize / 2.0), (aPos.y + cubeSize * 2 + (cubeSize / 2.0)) + 75.0, aPos.z);
    glEnd();


    glEndList();

    //H
    glNewList(3, GL_COMPILE);

    for(int i = 0; i < 4; i++)
    {
      glPushMatrix();
      glTranslatef(hPos.x, hPos.y - cubeSize * i, hPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }

    for(int i = 1; i < 3; i++)
    {
      glPushMatrix();
      glTranslatef(hPos.x + cubeSize * i, hPos.y - cubeSize * 2, hPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }

    for(int i = 0; i < 4; i++)
    {
      glPushMatrix();
      glTranslatef(hPos.x + cubeSize * 3, hPos.y - cubeSize * i, hPos.z);
      glutSolidCube(cubeSize);
      glPopMatrix();
    }

    glEndList();


  // Event setup
  glutDisplayFunc(display_CB);
  glutTimerFunc(1000 / framerate, timer_CB, 0);
  glutTimerFunc(1000, timer_CB, 1);
  glutTimerFunc(55, timer_CB, 2);

  glutMainLoop();
  return 0;
}