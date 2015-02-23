#include <GL/freeglut.h>

static void callback_renderscene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test 1");

    glutDisplayFunc(callback_renderscene);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glutMainLoop();

    return EXIT_SUCCESS;
}
