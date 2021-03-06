#include "node_graphic.h"

#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

Scene::Node * root_node = nullptr;

static void draw() {
    // static Scene::Node::transform_type view = glm::lookAt(
    //         glm::vec3(0, 0.1, 50.0),
    //         glm::vec3(0, 0, 0),
    //         glm::vec3(0, 0, -1));
    static Scene::Node::transform_type proj = glm::ortho(
            0.0f, 1024.0f,
            0.0f, 768.0f,
            0.0f, 1000.f);

    if(root_node == nullptr)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    root_node->draw_all(proj, Scene::Node::rectangle_type(0, 0, 1, 1));
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Test");
    glutReshapeWindow(1024, 768);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);

    Scene::Node * root = new Scene::Node("root");
    root->apply(Scene::Node::scale_type(0.2, 0.2));
    root_node = root;

    Texture * tile = new Texture("./assets/tile1.png");
    for(unsigned int x = 0 ; x < 5 ; x++) {
        for(unsigned int y = 0 ; y < 4 ; y++) {
            Scene::Graphic * g = new Scene::Graphic("", root);
            g->texture(tile);
            g->apply(Scene::Node::translation_type(450.0 * x, 450.0 * y, 0.0));
        }
    }

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
