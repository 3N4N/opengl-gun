#ifndef _VECTOR_H_
#define _VECTOR_H_

struct vector
{
    double x,y,z;
};

vector cross_product(vector a, vector b);
double dot_product(vector a, vector b);

#endif // _VECTOR_H_

