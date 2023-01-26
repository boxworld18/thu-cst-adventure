#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"
#include "camera_controller.hpp"

#include <string>
#include <glut.h>

using namespace std;

// Global variables used by UI handlers.
// Of course you can use partial lambda functions to make things more graceful.
SceneParser *sceneParser;
CameraController *cameraController;
int imgW, imgH;
string savePicturePath;

void screenCapture() {
    Image openglImg(imgW, imgH);
    auto *pixels = new unsigned char[3 * imgW * imgH];
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    //glReadBuffer(GL_BACK);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, imgW, imgH, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    for (int x = 0; x < imgW; ++x) {
        for (int y = 0; y < imgH; ++y) {
            Vector3f color(
                    pixels[3 * (y * imgW + x) + 0] / 255.0,
                    pixels[3 * (y * imgW + x) + 1] / 255.0,
                    pixels[3 * (y * imgW + x) + 2] / 255.0);
            openglImg.SetPixel(x, y, color);
        }
    }
    openglImg.SaveImage(savePicturePath.c_str());
    delete[] pixels;
    cout << "Current viewport captured at " << savePicturePath << "." << endl;
}

//  Called when mouse button is pressed.
void mouseFunc(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {

        switch (button) {
            case GLUT_LEFT_BUTTON:
                cameraController->mouseClick(CameraController::LEFT, x, y);
                break;
            case GLUT_MIDDLE_BUTTON:
                cameraController->mouseClick(CameraController::MIDDLE, x, y);
                break;
            case GLUT_RIGHT_BUTTON:
                cameraController->mouseClick(CameraController::RIGHT, x, y);
            default:
                break;
        }
    } else {
        cameraController->mouseRelease(x, y);
    }
    glutPostRedisplay();
}

// Called when mouse is moved while button pressed.
void motionFunc(int x, int y) {
    cameraController->mouseDrag(x, y);
    glutPostRedisplay();
}

// Called when the window is resized
void reshapeFunc(int w, int h) {
    sceneParser->getCamera()->resize(w, h);
    glViewport(0, 0, w, h);
    imgW = w;
    imgH = h;
}

// This function is responsible for displaying the object.
void drawScene() {
    Vector3f backGround = sceneParser->getBackgroundColor();
    glClearColor(backGround.x(), backGround.y(), backGround.z(), 1.0);

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup MODELVIEW Matrix
    sceneParser->getCamera()->setupGLMatrix();

    // Turn On all lights.
    for (int li = 0; li < sceneParser->getNumLights(); ++li) {
        Light *light = sceneParser->getLight(li);
        light->turnOn(li);
    }
    // Draw elements.
    Group *baseGroup = sceneParser->getGroup();
    baseGroup->drawGL();

    // Dump the image to the screen.
    glutSwapBuffers();

    // Save if not in interactive mode.
    if (!savePicturePath.empty()) {
        screenCapture();
        exit(0);
    }
}

float getCenterDepth() {
    Camera *cam = sceneParser->getCamera();
    Ray centerRay = sceneParser->getCamera()->generateRay(
            Vector2f((float) cam->getWidth() / 2, (float) cam->getHeight() / 2));
    Hit hit;
    bool isHit = sceneParser->getGroup()->intersect(centerRay, hit, 0.0);
    return isHit ? hit.getT() : 10.0f;
}

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3 && argc != 2) {
        cout << "Usage: PA2 <input scene file> [output image file]" << endl;
        cout << "  If the output path is not specified, program will enter interactive mode." << endl;
        return 1;
    }

    // Load Scene as before.
    sceneParser = new SceneParser(argv[1]);
    Camera *cam = sceneParser->getCamera();
    float lookAtDistance = getCenterDepth();
    cameraController = new CameraController(dynamic_cast<PerspectiveCamera *>(cam), lookAtDistance);

    if (argc == 3) savePicturePath = argv[2];
    cout << "Look At Distance = " << lookAtDistance << endl;

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(60, 60);
    glutInitWindowSize(cam->getWidth(), cam->getHeight());
    glutCreateWindow("PA2 BezierSurface");

    // Depth testing must be turned on
    glEnable(GL_DEPTH_TEST);
    // Enable lighting calculations
    glEnable(GL_LIGHTING);
    // In case for non-uniform transform.
    glEnable(GL_NORMALIZE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Set up callback functions for mouse
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    // Set up the callback function for resizing windows
    glutReshapeFunc(reshapeFunc);

    // Call this whenever window needs redrawing
    glutDisplayFunc(drawScene);

    // Main UI Loop. This never returns.
    glutMainLoop();

    return 0;
}

