#include "Game.h"

#include <GL/glut.h>
#include <stdlib.h>

void draw();
void update(int value);
void handleKeyPress(unsigned char key, int x, int y);
void handleKeyRelease(unsigned char key, int x, int y);
void handleMouseDown(int button, int state, int x, int y);
void handleMouseMove(int x, int y);
void reshape(int new_width, int new_height);

extern Game game;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Cave Explorer");

    glClearColor(0.1f, 0.02f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 0, 1);

    glutDisplayFunc(draw);

    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutMouseFunc(handleMouseDown);
    glutPassiveMotionFunc(handleMouseMove);
    glutReshapeFunc(reshape);

    game.screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    game.screenHeight = glutGet(GLUT_WINDOW_HEIGHT);

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
    glColor3f(0.3, 0.1, 0.0);

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

// Mouse handling
void handleMouseDown(int button, int state, int x, int y)
{
    game.mouseDown(button, state, x, y);
    glutMotionFunc(handleMouseMove);
}

void handleMouseMove(int x, int y)
{
    game.mouseMove(x, y);
}

void reshape(int new_width, int new_height)
{
    game.reshape(new_width, new_height);
}
