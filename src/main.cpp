#include<stdio.h>
// #include<stdlib.h>
#include<math.h>

#include <GL/glut.h>

#include "point.h"
#include "vector.h"
#include "glutshapes.h"

#define ROTSPEED 0.8
#define MOVSPEED 3

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double gun_z_rot;
double gun_y_rot;
double bar_z_rot;
double bar_x_rot;

point cam_pos;
vector cam_u,cam_l,cam_r;


void keyboardListener(unsigned char key, int x,int y)
{
    double radangle = ROTSPEED / 57.2957795;
    vector _l, _r, _u;
    _l.x = cam_l.x; _l.y = cam_l.y; _l.z = cam_l.z;
    _r.x = cam_r.x; _r.y = cam_r.y; _r.z = cam_r.z;
    _u.x = cam_u.x; _u.y = cam_u.y; _u.z = cam_u.z;

    switch(key){

        case '1':
            cam_l.x = _l.x * cos(radangle) - _r.x * sin(radangle);
            cam_l.y = _l.y * cos(radangle) - _r.y * sin(radangle);
            cam_l.z = _l.z * cos(radangle) - _r.z * sin(radangle);
            cam_r = cross_product(cam_l, cam_u);
            break;
        case '2':
            cam_l.x = _l.x * cos(-1 * radangle) - _r.x * sin(-1 * radangle);
            cam_l.y = _l.y * cos(-1 * radangle) - _r.y * sin(-1 * radangle);
            cam_l.z = _l.z * cos(-1 * radangle) - _r.z * sin(-1 * radangle);
            cam_r = cross_product(cam_l, cam_u);
            break;

        case '3':
            cam_l.x = _l.x * cos(radangle) + _u.x * sin(radangle);
            cam_l.y = _l.y * cos(radangle) + _u.y * sin(radangle);
            cam_l.z = _l.z * cos(radangle) + _u.z * sin(radangle);
            cam_u = cross_product(cam_r, cam_l);
            break;
        case '4':
            cam_l.x = _l.x * cos(-1 * radangle) + _u.x * sin(-1 * radangle);
            cam_l.y = _l.y * cos(-1 * radangle) + _u.y * sin(-1 * radangle);
            cam_l.z = _l.z * cos(-1 * radangle) + _u.z * sin(-1 * radangle);
            cam_u = cross_product(cam_r, cam_l);
            break;

        case '5':
            cam_u.x = _u.x * cos(-1 * radangle) + _r.x * sin(-1 * radangle);
            cam_u.y = _u.y * cos(-1 * radangle) + _r.y * sin(-1 * radangle);
            cam_u.z = _u.z * cos(-1 * radangle) + _r.z * sin(-1 * radangle);
            cam_r = cross_product(cam_l, cam_u);
            break;
        case '6':
            cam_u.x = _u.x * cos(radangle) + _r.x * sin(radangle);
            cam_u.y = _u.y * cos(radangle) + _r.y * sin(radangle);
            cam_u.z = _u.z * cos(radangle) + _r.z * sin(radangle);
            cam_r = cross_product(cam_l, cam_u);
            break;

        case 'q':
            gun_z_rot = (gun_z_rot + 5) > 45 ? 45 : gun_z_rot + 5;
            break;
        case 'w':
            gun_z_rot = (gun_z_rot - 5) < -45 ? -45 : gun_z_rot - 5;
            break;

        case 'e':
            gun_y_rot = (gun_y_rot + 5) > 45 ? 45 : gun_y_rot + 5;
            break;
        case 'r':
            gun_y_rot = (gun_y_rot - 5) < -45 ? -45 : gun_y_rot - 5;
            break;

        case 'a':
            bar_z_rot = (bar_z_rot + 5) > 45 ? 45 : bar_z_rot + 5;
            break;
        case 's':
            bar_z_rot = (bar_z_rot - 5) < -45 ? -45 : bar_z_rot - 5;
            break;

        case 'd':
            bar_x_rot = (bar_x_rot + 5) > 45 ? 45 : bar_x_rot + 5;
            break;
        case 'f':
            bar_x_rot = (bar_x_rot - 5) < -45 ? -45 : bar_x_rot - 5;
            break;

        default:
            break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key){
        case GLUT_KEY_UP:       // up arrow key
            // cameraHeight += 3.0;
            cam_pos.x += cam_l.x * MOVSPEED;
            cam_pos.y += cam_l.y * MOVSPEED;
            cam_pos.z += cam_l.z * MOVSPEED;
            break;
        case GLUT_KEY_DOWN:     //down arrow key
            // cameraHeight -= 3.0;
            cam_pos.x -= cam_l.x * MOVSPEED;
            cam_pos.y -= cam_l.y * MOVSPEED;
            cam_pos.z -= cam_l.z * MOVSPEED;
            break;

        case GLUT_KEY_RIGHT:
            // cameraAngle += 0.03;
            cam_pos.x += cam_r.x * MOVSPEED;
            cam_pos.y += cam_r.y * MOVSPEED;
            cam_pos.z += cam_r.z * MOVSPEED;
            break;
        case GLUT_KEY_LEFT:
            // cameraAngle -= 0.03;
            cam_pos.x -= cam_r.x * MOVSPEED;
            cam_pos.y -= cam_r.y * MOVSPEED;
            cam_pos.z -= cam_r.z * MOVSPEED;
            break;

        case GLUT_KEY_PAGE_UP:
            cam_pos.x += cam_u.x * MOVSPEED;
            cam_pos.y += cam_u.y * MOVSPEED;
            cam_pos.z += cam_u.z * MOVSPEED;
            break;
        case GLUT_KEY_PAGE_DOWN:
            cam_pos.x -= cam_u.x * MOVSPEED;
            cam_pos.y -= cam_u.y * MOVSPEED;
            cam_pos.z -= cam_u.z * MOVSPEED;
            break;

        default:
            break;
    }
}


void mouseListener(int button, int state, int x, int y)
{
    //x, y is the x-y of the screen (2D)
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){     // 2 times?? in ONE click? -- solution is checking DOWN or UP
                drawaxes=1-drawaxes;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            //........
            break;

        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
    }
}



void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);  //color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(100,100,100,    0,0,0,  0,0,1);
    // gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,       0,0,0,      0,0,1);
    gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z,
              cam_pos.x + cam_l.x, cam_pos.y + cam_l.y, cam_pos.z + cam_l.z,
              cam_u.x, cam_u.y, cam_u.z);
    // gluLookAt(0,0,200,  0,0,0,  0,1,0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes(drawaxes);
    drawGrid(drawgrid);

    double sphereRadius = 30;
    double halfSphereRadius = 10;
    double cylinderHeight = 100;

    glRotatef(90,1,0,0);
    glRotatef(gun_z_rot,0,1,0);
    drawHalfSphere(sphereRadius,80,20,1);
    glRotatef(-90,1,0,0);

    glRotatef(-90,1,0,0);
    glRotatef(gun_y_rot,1,0,0);
    drawHalfSphere(sphereRadius,80,20,0);
    glRotatef(90,1,0,0);

    glTranslatef(0,sphereRadius + halfSphereRadius,0);
    glRotatef(90,1,0,0);
    glRotatef(bar_z_rot,0,1,0);
    glRotatef(bar_x_rot,0,0,1);
    drawHalfSphere(halfSphereRadius,80,20,0);
    glRotatef(-90,1,0,0);

    glTranslatef(0,cylinderHeight,0);
    glRotatef(90,1,0,0);
    drawCylinder(halfSphereRadius,cylinderHeight,80,20);
    glRotatef(-90,1,0,0);
    glRotatef(-90,1,0,0);
    drawHorn(halfSphereRadius,80,20);


    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=1.50;
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid=0;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;

    cam_pos.x = 100;
    cam_pos.y = 100;
    cam_pos.z = 0;

    cam_u.x = 0;
    cam_u.y = 0;
    cam_u.z = 1;

    cam_r.x = -1.0/sqrt(2);
    cam_r.y = 1.0/sqrt(2);
    cam_r.z = 0;

    cam_l.x = -1.0/sqrt(2);
    cam_l.y = -1.0/sqrt(2);
    cam_l.z = 0;

    gun_y_rot = 0.0;
    gun_z_rot = 0.0;
    bar_z_rot = 0.0;
    bar_x_rot = 0.0;


    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,  1,  1,  1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);   //Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);    //enable Depth Testing

    glutDisplayFunc(display);   //display callback function
    glutIdleFunc(animate);      //what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();     //The main loop of OpenGL

    return 0;
}
