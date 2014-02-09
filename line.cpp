#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <GL/glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)


// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);

void keyboardexit(unsigned char key, int x, int y);
void keyboardpress(int key, int x, int y);
void Mouseclick(int button, int state, int x, int y);


// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 


int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int width = glutGet(GLUT_SCREEN_WIDTH);
    int height = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = width * 2 / 3;
    int windowHeight = height * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Hello World");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(keyboardexit);
    glutSpecialFunc(keyboardpress);
    glutMouseFunc(Mouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}


// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();


	// Draw line

	// Draw World
	

    // Draw Box
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBox(box_len);
    
    // Draw Ball
    glPushMatrix();
    glTranslatef(ball_x, ball_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    // Draw Triangle
    glPushMatrix();
    glTranslatef(tri_x, tri_y, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawTriangle();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
    
    // Handle ball collisions with box
    if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;
    
    // Update position of ball
    ball_x += ball_velx;
    ball_y += ball_vely;

    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboardexit(unsigned char key, int x, int y) {

    if (key == 27 || key == 'q') {
        exit(0);     // escape or q key is pressed
    }
    if (state == GLUT_DOWN)
    {
        if (key == 'r')
            theta = theta + 15;
        else if (key == 'l')
            theta = theta - 15;
    }
}

void keyboardpress(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;        
}

void Mouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta = theta + 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta = theta - 15;
    }
}



