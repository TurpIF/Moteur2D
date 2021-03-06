#include "texture.h"

#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

static void draw(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Test");
    glutReshapeWindow(1024, 768);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(0.0, 0.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DITHER);
    // glEnable(GL_TEXTURE_2D);
    // glShadeModel(GL_SMOOTH);
    // glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    // glClearDepth(1.0f);
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    for(unsigned int i = 0 ; i < 10 ; i++)
    {
        {
            Texture t("test.png");
            std::cout
                << "; id : " << t.id()
                << "; wi : " << t.width()
                << "; he : " << t.height()
                << std::endl;
        }
        {
            Texture t("test2.png");
            std::cout
                << "; id : " << t.id()
                << "; wi : " << t.width()
                << "; he : " << t.height()
                << std::endl;
        }
    }

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
