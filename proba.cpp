#include <GLUT/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Number of points to generate
const int NUM_POINTS = 5;

// Structure to represent a 3D point
struct Point3D {
    float x;
    float y;
    float z;
};

// Array to store the randomly generated points
Point3D points[NUM_POINTS];

// Rotation angles for the plot
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
int lastMouseX = 0;
int lastMouseY = 0;
float zoom = 1.0f;

void generateRandomPoints()
{
    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Generate random points within the range [-1.0, 1.0]
    for (int i = 0; i < NUM_POINTS; ++i) {
        points[i].x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0 - 1.0;
        points[i].y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0 - 1.0;
        points[i].z = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0 - 1.0;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the camera position and apply rotations and zoom
    gluLookAt(0.0, 0.0, 5.0 / zoom,  // Eye position
              0.0, 0.0, 0.0,         // Look-at point
              0.0, 1.0, 0.0);        // Up vector
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    
    // Draw the coordinate system axes
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    
    // Draw the points as small spheres
    glColor3f(1.0, 0.0, 0.0); // Red
    
    for (int i = 0; i < NUM_POINTS; ++i) {
        glPushMatrix();
        glTranslatef(points[i].x, points[i].y, points[i].z);
        glutSolidSphere(0.05, 10, 10);
        glPopMatrix();
    }
    
    // Draw the connections between points
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0); // Blue
    
    for (int i = 0; i < NUM_POINTS; ++i) {
        glVertex3f(points[i].x, points[i].y, points[i].z);
        
        // Connect the current point with the next point
        if (i < NUM_POINTS - 1) {
            glVertex3f(points[i + 1].x, points[i + 1].y, points[i + 1].z);
        }
    }
    
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
    
    if (button == 3) { // Mouse roller up
        zoom /= 1.1;
    } else if (button == 4) { // Mouse roller down
        zoom *= 1.1;
    }
    
    glutPostRedisplay();
}

void motion(int x, int y)
{
    rotationX += (y - lastMouseY) * 0.2f;
    rotationY += (x - lastMouseX) * 0.2f;
    lastMouseX = x;
    lastMouseY = y;
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) { // Escape key
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Random Points");
    
    glEnable(GL_DEPTH_TEST);
    
    // Set the background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    generateRandomPoints();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}

