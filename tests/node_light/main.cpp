#include "node_light.h"

#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

Scene::Node * root_node = nullptr;

static void draw() {
    static Scene::Node::transform_type proj = glm::ortho(
            0.0f, 1024.0f,
            0.0f, 768.0f,
            0.0f, 1000.f);

    if(root_node == nullptr)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    root_node->draw_all(proj, Scene::Node::rectangle_type(0, 0, 1, 1));

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
    root_node = root;

    Scene::Light * light1 = new Scene::Light("light1", root);
    light1->color(1.0, 0.0, 0.0);
    light1->radius(300.f);
    light1->quality(Scene::Light::quality_type(16));
    light1->apply(Scene::Node::translation_type(500, 500, 0));

    float dist = 100.0f;
    float sinpi_3 = 0.86f;
    float cospi_3 = 0.5f;

    Scene::Light * light2 = new Scene::Light("light2", light1);
    light2->color(0.0, 1.0, 0.0);
    light2->radius(300.f);
    light2->quality(Scene::Light::quality_type(16));
    light2->apply(Scene::Node::translation_type(dist, 0, 0));

    Scene::Light * light3 = new Scene::Light("light3", light1);
    light3->color(0.0, 0.0, 1.0);
    light3->radius(300.f);
    light3->quality(Scene::Light::quality_type(16));
    light3->apply(Scene::Node::translation_type(dist * cospi_3, dist * sinpi_3, 0));

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
