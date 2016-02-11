#include "Game.h"

#include <GL/glut.h>
#include <stdlib.h>

void draw();
void update(int value);
void handleKeyPress(unsigned char key, int x, int y);
void handleKeyRelease(unsigned char key, int x, int y);

Game game;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Cave Explorer");

    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 0, 1);

    glutDisplayFunc(draw);

    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);

    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return EXIT_SUCCESS;
}

void update(int value)
{
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);

    game.update();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

    game.draw();

	glFlush();
}

// Key handling
void handleKeyPress(unsigned char key, int x, int y)
{
    game.keyPress(key);
}

void handleKeyRelease(unsigned char key, int x, int y)
{
    game.keyRelease(key);
}
