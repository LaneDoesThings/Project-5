/*
CS445/545 Prog 5 for Lane Wright

The letters are drawn as a set of cubes using display lists and are updated via
their global angle variable that is updated in the timer_CB function. The
letters are subject to ambient lighting with strong specular elements.

The display_CB function is used to draw the letters as well as to
upadte the display.

The events that are used are a display event, timer event, and keyboard event
with their respective callbacks mentioned above.
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-aug24.h"

#define canvas_Width 800
#define canvas_Height 800
#define framerate 60

#define cubeSize 50.0
#define cubeStart -400.0
#define groundPlane -200.0

// Just to make my life easier when positioning things
struct vec3 {
  double x;
  double y;
  double z;
};

// Starting position for the first block in the three letters
struct vec3 uPos = {.x = (-cubeSize * 6) - (cubeSize / 2),
                    .y = groundPlane + (cubeSize * 2),
                    .z = cubeStart};
struct vec3 aPos = {
    .x = (-cubeSize) - (cubeSize / 2), .y = groundPlane, .z = cubeStart};
struct vec3 hPos = {.x = (cubeSize * 4) - (cubeSize / 2),
                    .y = groundPlane + (cubeSize * 2),
                    .z = cubeStart};

float lightpos[4] = {0.0, 0.0, 0.0, 1.0};   // Origin positional light
float lightcolor[4] = {1.0, 1.0, 1.0, 1.0}; // White

float uahMaterial[4] = {0.0, 0.47, 0.78, 1.0}; // UAH color
float silverMaterial[4] = {0.75, 0.75, 0.75, 1.0};
float candyAppleMaterial[4] = {1.0, 0.031, 0.0, 1.0};
float grayMaterial[4] = {0.25, 0.25, 0.25, 1.0};
float specular = 50.0; // Specular exponent

float angle = 0;

// Callback for display event that calls the display lists that will draw all
// the objects in the scene
void display_CB() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Draws and rotates the cubes
  glPushMatrix();
  glTranslatef((aPos.x + cubeSize) + (cubeSize / 2.0), 0.0, cubeStart);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glTranslatef(-((aPos.x + cubeSize) + (cubeSize / 2.0)), 0.0, -cubeStart);
  glCallList(1);
  glCallList(2);
  glCallList(3);
  glPopMatrix();

  // Draws the spindle
  glMaterialfv(GL_FRONT, GL_AMBIENT, grayMaterial);
  glDisable(GL_LIGHT0);
  glBegin(GL_TRIANGLES);
  glVertex3f(aPos.x + cubeSize,
             (aPos.y + cubeSize * 2 + (cubeSize / 2.0)) + 75.0, aPos.z);
  glVertex3f(aPos.x + cubeSize * 2,
             (aPos.y + cubeSize * 2 + (cubeSize / 2.0)) + 75.0, aPos.z);
  glVertex3f((aPos.x + cubeSize) + (cubeSize / 2.0),
             aPos.y + cubeSize * 2 + (cubeSize / 2.0), aPos.z);
  glEnd();

  glutSwapBuffers();
}

// Callback for timer event that handles the framerate and
// the timer for rotating the letters
void timer_CB(int id) {
  // Framerate
  if (id == 0) {
    glutTimerFunc(1000 / framerate, timer_CB, 0);
    glutPostRedisplay();
  }
  // Rotation
  if (id == 1) {
    angle += 4 % 360;
    glutTimerFunc(22.2, timer_CB, 1);
  }
}

int main(int argc, char *argv[]) {
  char canvas_Name[] = "Project 5 - Lane Wright";
  glutInit(&argc, argv);
  my_setup(canvas_Width, canvas_Height, canvas_Name);
  glGenLists(3);

  // U
  glNewList(1, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, uahMaterial);
  glMaterialfv(GL_FRONT, GL_SPECULAR, lightcolor);
  glMaterialf(GL_FRONT, GL_SHININESS, specular);

  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glTranslatef(uPos.x, uPos.y - cubeSize * i, uPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }
  for (int i = 1; i < 4; i++) {
    glPushMatrix();
    glTranslatef(uPos.x + cubeSize * i, uPos.y - cubeSize * 3, uPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  for (int i = 0; i < 3; i++) {
    glPushMatrix();
    glTranslatef(uPos.x + cubeSize * 3, uPos.y - cubeSize * i, uPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  glEndList();

  // A
  glNewList(2, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, silverMaterial);

  for (int i = 0; i < 4; i++) {
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
  glTranslatef(aPos.x + cubeSize * 2 + (cubeSize / 2), aPos.y + cubeSize,
               aPos.z);
  glutWireCube(cubeSize);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(aPos.x + cubeSize * 3 + (cubeSize / 2), aPos.y - cubeSize,
               aPos.z);
  glutWireCube(cubeSize);
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT, candyAppleMaterial);
  glMaterialfv(GL_FRONT, GL_SPECULAR, lightcolor);
  glMaterialf(GL_FRONT, GL_SHININESS, specular);
  glPushMatrix();
  glTranslatef(aPos.x + cubeSize + (cubeSize / 2.0), aPos.y + cubeSize, aPos.z);
  glutSolidSphere(cubeSize / 2.0, 25, 10);
  glPopMatrix();

  glEndList();

  // H
  glNewList(3, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, uahMaterial);
  glMaterialfv(GL_FRONT, GL_SPECULAR, lightcolor);
  glMaterialf(GL_FRONT, GL_SHININESS, specular);

  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glTranslatef(hPos.x, hPos.y - cubeSize * i, hPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  for (int i = 1; i < 3; i++) {
    glPushMatrix();
    glTranslatef(hPos.x + cubeSize * i, hPos.y - cubeSize * 2, hPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glTranslatef(hPos.x + cubeSize * 3, hPos.y - cubeSize * i, hPos.z);
    glutSolidCube(cubeSize);
    glPopMatrix();
  }

  glEndList();

  // Event setup
  glutDisplayFunc(display_CB);
  glutTimerFunc(1000 / framerate, timer_CB, 0);
  glutTimerFunc(22.2, timer_CB, 1);

  glutMainLoop();
  return 0;
}