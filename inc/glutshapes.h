#ifndef _GLUT_SHAPES_H_
#define _GLUT_SHAPES_H_

#include <GL/glut.h>

void drawAxes(int drawaxes);
void drawSquare(double a);
void drawGrid(int drawgrid);
void drawCircle(double radius,int segments);
void drawCone(double radius,double height,int segments);
void drawHalfSphere(double radius,int slices,int stacks, int reverse);
void drawSphere(double radius,int slices,int stacks);
void drawCylinder(double radius, double height, int slices, int stacks);
void drawHorn(double radius, int slices, int stacks);
void drawSS(double angle);

#endif // _GLUT_SHAPES_H_
