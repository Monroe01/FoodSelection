//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Official Name: Menglu Liu
// E-mail: mliu40@syr.edu
// *
//Assignment: Assignment 2
// * Environment/Compiler: Visual Studio Community 2022
// Date submitted: February 19, 2025

// mouse clicks: click to select food you want, right click for pop menu
// Keyboard interaction :  Press the escape key to quit.

////////////////////////////////////////////////////////////////////////////////////////////////////////




#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159


//global
float plateRotation = 0.0;




// Text
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
    }
}

// Circle
void drawCircle(float cx, float cy, float r, bool filled) {
    glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * PI / 180.0;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

// Square
void drawSquare(float x, float y, float size, bool filled) {
    glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}





// Food names
const char* mainDishes[] = {"Pizza", "Sushi"};
const char* sideDishes[] = {"Cheese", "Egg", "Pepperoni"};
const char* sideDishes1[] = {"Cucumber", "Egg"};

//selected state
int selectedMainDish = -1;
bool selectedSideDishes[3] = {false, false, false};

const char* plateColor[] = {"red", "white","grey"};
bool selectedPlate[3] ={false, false, false};

int selectedPlateShape = 1; // 0: Square, 1: Circle

//sides
void drawSide(){
    if (selectedMainDish == 0) {
        drawText(0.2, 0.6, "Sides");
        for (int i = 0; i < 3; i++) {
            float x = 0.1, y = 0.35 - i * 0.2;
            drawSquare(x, y, 0.05, selectedSideDishes[i]);
            drawText(x + 0.1, y - 0.01, sideDishes[i]);
        }
    }
    
    if (selectedMainDish == 1) {
        drawText(0.2, 0.6, "Sides 1");
        for (int i = 0; i < 2; i++) {
            float x = 0.1, y = 0.35 - i * 0.2;
            drawSquare(x, y, 0.05, selectedSideDishes[i]);
            drawText(x + 0.1, y - 0.01, sideDishes1[i]);
        }
    }
}

// foodslection
void drawfoodselection() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    
    drawText(-0.15, 0.85, "Food Selection");

    drawText(-0.65, 0.6, "Main");
    for (int i = 0; i < 2; i++) {
        float x = -0.75, y = 0.35 - i * 0.2;
        drawCircle(x, y, 0.04, selectedMainDish == i);
        drawText(x + 0.1, y - 0.01, mainDishes[i]);
    }


    drawSide();
    glFlush();
}


//egg
void drawEgg(float x, float y, float z) {
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.9);
    glTranslatef(x, y, z);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0, 0.8, 0.0);
    glTranslatef(x, y + 0.1, z);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
}


// cheese
void drawCheese(float x, float y, float z) {
    glPushMatrix();
    glColor3f(1.0, 0.5, 0);
    glTranslatef(x, y, z);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

//Cucumber
void drawCucumber(float x, float y, float z) {
    glPushMatrix();
    glColor3f(0, 0.5, 0.0);
    glTranslatef(x, y, z);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
}

//Pepeperoni
void drawPepperoni(){
    float r = 0.15f;
    float positions[5][2] = {
        {0.3f, 0.3f}, {-0.4f, 0.2f}, {0.2f, -0.3f},
        {-0.3f, -0.4f}, {0.0f, 0.0f}
    };
    
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(positions[i][0], positions[i][1], 0.11f);
        drawCircle(0, 0, r, true);
        glPopMatrix();
    }
}

//Pizza
void drawPizza() {
    GLUquadric* quad = gluNewQuadric();
    
    glRotatef(plateRotation, 0, 1, 0);
    glPushMatrix();
    glColor3f(1.0, 0.7, 0.2);
    glTranslatef(0.0, -0.5, 0.0);
    glRotatef(-90, 1, 0, 0);


    gluCylinder(quad, 1.0, 1.0, 0.1, 50, 10);

    glColor3f(1.0, 0.9, 0.0);
    gluDisk(quad, 0.0, 1.0, 50, 10);

    glColor3f(0.8, 0.1, 0.1);
  
    if(selectedSideDishes[2]){
        drawPepperoni();
    }
    if (selectedSideDishes[1]) {
        drawEgg(0.0, 0.1, 0.2);
    }
    if (selectedSideDishes[0]) {
        drawCheese(0.1, -0.5, 0);
        drawCheese(.4, .2, 0);
        drawCheese(-.5, -.5, 0);
        drawCheese(.5, .5, 0);
        drawCheese(.1, .5, 0);
    }


    
    glPopMatrix();

}


// Sushi
void drawSushi() {
    glRotatef(plateRotation, 0, 1, 0);
    glPushMatrix();

    
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0, -.2, 0);
    glScalef(1.5, 0.7, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.1, 0.1, 0.1);
    

    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(0.0, -.2, i * 0.5);
        glScalef(1.5, 0.7, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // fish (0.0, 0.35, 0.0)
    glColor3f(1.0, 0.3, 0.3);
    glPushMatrix();
    glTranslatef(0.0, .2, 0.0);
    glScalef(1.3, 0.2, 0.8);
    glutSolidCube(1.0);
    glPopMatrix();
    
    if (selectedSideDishes[0]) {
        drawCucumber(0.0, 0.5, -.2);
    }
    if (selectedSideDishes[1]) {
        drawEgg(0.0, 0.5, .2);
    }
    glPopMatrix();
}


// plate
// glTranslatef(0.0, -0.6, 0.0);
void drawPlate() {
    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();

    glRotatef(plateRotation, 0, 1, 0);
    
    if (selectedPlate[0]) glColor3f(1.0, 0.0, 0.0); // Red
    else if (selectedPlate[1]) glColor3f(1.0, 1.0, 1.0); // White
    else if (selectedPlate[2]) glColor3f(0.5, 0.5, 0.5); // Grey
    else glColor3f(0.9, 0.9, 0.9); // Default

    glTranslatef(0.0, -0.6, 0.0);
    glRotatef(-90, 1, 0, 0);

    if (selectedPlateShape == 1) { // circle
        gluDisk(quad, 0.0, 1.4, 50, 10);
        gluCylinder(quad, 1.4, 1.5, 0.05, 50, 10);
        glTranslatef(0.0, 0.0, 0.05);
        gluDisk(quad, 0.0, 1.5, 50, 10);
    } else { // square
        glBegin(GL_QUADS);
        glVertex3f(-1.5, -1.5, 0);
        glVertex3f(1.5, -1.5, 0);
        glVertex3f(1.5, 1.5, 0);
        glVertex3f(-1.5, 1.5, 0);
        glEnd();
    }

    glPopMatrix();
}


void displayFoodDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 05, 1,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    
    drawPlate();
    
    if (selectedMainDish == 0) {
        drawPizza();
    } else if (selectedMainDish == 1) {
        drawSushi();
    }

    glFlush();
}



void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float mx = (x / (400 / 2.0)) - 1.0;
        float my = 1.0 - (y / (400 / 2.0));

        //main food
        for (int i = 0; i < 2; i++) {
            float bx = -0.75, by = 0.35 - i * 0.2;
            float dist = (mx - bx) * (mx - bx) + (my - by) * (my - by);
            if (dist < 0.0016) {
                selectedMainDish = i;


                glutSetWindow(glutGetWindow());
                glutPostRedisplay();

                
                glutSetWindow(glutGetWindow() + 1);
                glutPostRedisplay();
                return;
            }
        }

        //sides
        for (int i = 0; i < 3; i++) {
            float bx = 0.1, by = 0.35 - i * 0.2;
            if (mx > bx && mx < bx + 0.05 && my > by && my < by + 0.05) {
                selectedSideDishes[i] = !selectedSideDishes[i];

                glutSetWindow(glutGetWindow());
                glutPostRedisplay();


                glutSetWindow(glutGetWindow() + 1);
                glutPostRedisplay();
                return;
            }
        }
        
    }
}

void menuHandler(int option) {
    if (option >= 0 && option <= 2) {
        for (int i = 0; i < 3; i++) selectedPlate[i] = false;
        selectedPlate[option] = true;
    } else if (option == 3 || option == 4) { // shape
        selectedPlateShape = option - 3;
    } else if (option == 5) { //  0°
        plateRotation = 0.0;
    } else if (option == 6) { //  45°
        plateRotation = 45.0;
    } else if (option == 7) { //  90°
        plateRotation = 90.0;
    } else if (option == 8) { //  180°
        plateRotation = 180.0;
    }
    
    glutPostRedisplay();
}

void createMenu() {
    int colorMenu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Grey", 2);

    int shapeMenu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Square", 3);
    glutAddMenuEntry("Circle", 4);

    int rotateMenu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("0°", 5);
    glutAddMenuEntry("45°", 6);
    glutAddMenuEntry("90°", 7);
    glutAddMenuEntry("180°", 8);
    
    
    int mainMenu = glutCreateMenu(menuHandler);
    glutAddSubMenu("Plate Color", colorMenu);
    glutAddSubMenu("Plate Shape", shapeMenu);
    glutAddSubMenu("Rotate Plate", rotateMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void resize(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    //  FoodSelection
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("FoodSelection");
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(drawfoodselection);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyInput);
    
    //  FoodDisplay
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(550, 100);
    glutCreateWindow("FoodDisplay");

    glClearColor(0.7, 0.9, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(displayFoodDisplay);
    createMenu();
    glutKeyboardFunc(keyInput);
    
    glutMainLoop();
    return 0;
}
