//--------------------------------------------------------
// CAP5705 Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#define GLEW_STATIC
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"


// globals
//---------------------------------
// scene
Scene       *pScene = NULL;     // scene geometry and lights
RayTracer   *pRayTracer = NULL; // runs ray tracing algorithm
RenderMode   mode = LAMBERTIAN;

// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;


// Function Prototypes
// TO DO: Proj2 raytracer
// Nothing to do here but note:
// These are not actually used in this
// app unless you were to create a glut
// window loop in the main and add a display callback
// You do not need this but it is available
//--------------------------------------
void MouseMotionCallback(int x, int y);
void MouseCallback(int button, int state, int x, int y);
void KeyCallback(unsigned char key, int x, int y);
void SpecialKeyCallback(int key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void EnvironmentMapping(void);









//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//
void Setup(void)
{

    // init the scene
    pScene = new Scene();

    // TO DO: Proj2 raytracer
    // CAP5705 - Set up your scene.
    // Use the variable pScene to set parameters
    // 1. change background color
    // 2. add lights
    // 3. add objects
    // 4. add translation and rotation operations to place objects
    //------------------------------------------------

    //------------------------------------------------

    // init a ray tracer object
    RGBR_f color( 1.0, 0.0,0.0, 1 );
    RGBR_f bcolor(1.0, 1.0, 1.0, 1);
    Intersection* I = new Intersection();
    Sphere* s1 = new Sphere();
    Ray r;
    r.SetDirection(STVector3(1,1,0));
#if 0
    s1->mynewRadius(2.0);
    s1->mynewCentre(5.0, 2.4, 0.0);
    s1->FindIntersection(r, I );
#endif
    STVector3 pos(0, 0, 0);

     Triangle * s2 = new Triangle();
     s2->FindIntersection(r,I);
    Light l1(pos, color, "From origin");
    pScene->SetBackgroundColor(bcolor);
    pScene->AddLight(l1);
    //pScene->AddSurface(s1);

    pScene->AddSurface(s2);
    pRayTracer = new RayTracer();
    pRayTracer->Run(pScene, "test.JPG", mode);

}


//
// Reshape the window and record the size so
// that we can use it for screenshots.
//
void ReshapeCallback(int w, int h)
{
    gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // Set up a perspective projection
    float aspectRatio = (float) gWindowSizeX / (float) gWindowSizeY;
    gluPerspective(30.0f, aspectRatio, .1f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            pScene->GetCamera()->Strafe(10,0);
            break;
        case GLUT_KEY_RIGHT:
            pScene->GetCamera()->Strafe(-10,0);
            break;
        case GLUT_KEY_DOWN:
            pScene->GetCamera()->Strafe(0,-10);
            break;
        case GLUT_KEY_UP:
            pScene->GetCamera()->Strafe(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
    case 's': {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
        }
        break;
    case 'r':
        pScene->GetCamera()->Reset();
        break;
    case 'u':
        pScene->GetCamera()->ResetUp();
        break;
    case 'q':
        exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}


/**
 * Mouse event handler
 */
void MouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON
        || button == GLUT_RIGHT_BUTTON
        || button == GLUT_MIDDLE_BUTTON)
    {
        gMouseButton = button;
    } else
    {
        gMouseButton = -1;
    }

    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}


/**
 * Mouse active motion callback (when button is pressed)
 */
void MouseMotionCallback(int x, int y)
{
    if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
    {
        //compute delta
        float deltaX = x-gPreviousMouseX;
        float deltaY = y-gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;

        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON)
        {
            pScene->GetCamera()->Rotate(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_MIDDLE_BUTTON)
        {
            pScene->GetCamera()->Strafe(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_RIGHT_BUTTON)
        {
            pScene->GetCamera()->Zoom(deltaY);
        }

    } else
    {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }

}




//-----------------------------------------------
// Proj2 Ray Tracer
// This function follows the main
// logic of your rendering program.
// No command line inputs are necessary.
//-----------------------------------------------

void init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(640, 480);
    glutCreateWindow("proj1_mesh");
    //glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutSpecialFunc(SpecialKeyCallback);
    glutKeyboardFunc(KeyCallback);
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);
    //glutIdleFunc(DisplayCallback);
    glutMainLoop();
}
int main(int argc, char** argv)
{

    // TO DO: Proj2 raytracer
    // CAP5705 - Set the render mode.
    // 1. Add a commandline parameter for the render mode
    // 2. Remove the global variable
    //------------------------------------------------
        mode = LAMBERTIAN;
    //------------------------------------------------
    char* ch = argv[0];
    switch(*ch)
        {
        case '0':
            mode = LAMBERTIAN;
            break;
        case '1':
            mode = PHONG;
            break;
        case '2':
            mode = MIRROR;
            break;
        case '3':
            mode = ENVIRONMENTMAP;
            break;
        case '4':
            mode = EFFECT_1;
            break;
        case '5':
            mode = EFFECT_2;
            break;
        case '6':
            mode = EFFECT_3;
            break;
        }


    // Initializes the scene
        Setup();
        //Triangle* t1 = new Triangle;
        //t1->draw();
    // run the ray tracer
        init(argc,argv);
    pRayTracer->Run(pScene, "output.png", mode);


    return 0;
}


#pragma endregion
