#include "node_graphic.h"

#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

Scene::Node * root_node = nullptr;

static void draw(void) {
    if(root_node == nullptr)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    root_node->draw_all(Scene::Node::transform_type(), Scene::Node::rectangle_type(0, 0, 1024, 768));
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

    Scene::Graphic * g = new Scene::Graphic("root");
    g->texture(new Texture("./test.png"));
    g->apply(Scene::Node::translation_type(-0.1, -0.1, 0));
    g->apply(Scene::Node::rotation_type(30));
    root_node = g;

    Scene::Graphic * g2 = new Scene::Graphic("child1", root_node);
    g2->texture(new Texture("./test2.png"));
    g2->apply(Scene::Node::translation_type(-0.1, -0.1, 0));
    g2->apply(Scene::Node::rotation_type(30));

    Scene::Graphic * g3 = new Scene::Graphic("child2", g2);
    g3->texture(new Texture("./test3.png"));
    g3->apply(Scene::Node::translation_type(-0.1, -0.1, 0));
    g3->apply(Scene::Node::rotation_type(30));

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
