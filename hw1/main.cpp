#include <stdlib.h>
#include "../GL/glut.h"

void init(void);
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);

float cubeRx = 0.0, cubeRz = 0.0, appleR = 0.0, penR = 0.0, appleT = 0.0, penT = 0.0;
bool animationFlag = 0;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("OpenGL Assignment 1");
	glutReshapeWindow(512, 512);

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

void init(void) {

	GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void draw_pen(void)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.9 - 0.15);
	gluCylinder(gluNewQuadric(), 0.07, 0.0, 0.3, 20, 20);	// cone
	glPopMatrix();
	glTranslatef(0.0, 0.0, -0.75);
	gluCylinder(gluNewQuadric(), 0.07, 0.07, 1.5, 20, 20);	// cylinder
}

void draw_apple(void)
{
	glPushMatrix();
	glTranslatef(0.0, 0.57, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.03, 0.0, 0.3, 20, 20);	// cone1
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25, 0.73, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.03, 0.0, 0.3, 20, 20);	// cone2
	glPopMatrix();
	gluSphere(gluNewQuadric(), 0.6, 40, 40);
}

void draw_quad(float r, float g, float b, float a)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor4f(r, g, b, a);
	glVertex3f(-0.7, 0.7, 0.0);
	glVertex3f(-0.7, -0.7, 0.0);
	glVertex3f(0.7, -0.7, 0.0);
	glVertex3f(0.7, 0.7, 0.0);
	glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 8.0, /* Eye pos XYZ */
		0.0, 0.0, 0.0, /* Target pos XYZ */
		0.0, 1.0, 0.0); /* Up vector */

						// cube
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glPushMatrix();
	glTranslatef(0.0, 1.7, 0.0);
	glRotatef(cubeRx, 1.0, 0.0, 0.0);
	glRotatef(cubeRz, 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(0.0, 1.0, 0.0, 0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(1.0, 1.0, 0.0, 0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(0.0, 0.0, 1.0, 0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(1.0, 1.0, 1.0, 0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(1.0, 0.0, 0.0, 0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.7);
	draw_quad(0.5, 0.5, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_BLEND);

	if (!animationFlag) {
		appleT = 0.0;
		penT = 0.0;
	}
	else {
		appleR = 0.0;
		penR = 0.0;
	}

	// apple
	glPushMatrix();
	glTranslatef(1.5 + appleT, 0.0, 0.0);
	glRotatef(appleR, 0.0, 1.0, 0.0);
	draw_apple();
	glPopMatrix();

	// pen
	glPushMatrix();
	glTranslatef(-1.5 + penT, 0.0, 0.0);
	glRotatef(penR, 0.0, 1.0, 0.0);
	if (!animationFlag)
		glRotatef(-(90.0 + 15.0), 1.0, 0.0, 0.0);
	else {
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
	}
	draw_pen();
	glPopMatrix();

	glutSwapBuffers();

	cubeRx += 0.07;
	cubeRz += 0.07;
	if (!animationFlag) {
		appleR += 0.07;
		penR += 0.07;
	}
	else {	// animation (move to middle of screen)
		if (appleT > -1.5)
			appleT -= 0.015;
		if (penT < 1.5)
			penT += 0.015;
	}
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 13:
	{   //enter
		animationFlag = !animationFlag;
		break;
	}
	case 27:
	{   //ESC
		exit(0);
		break;
	}
	default:
	{
		break;
	}
	}
}

void idle(void)
{
	glutPostRedisplay();
}