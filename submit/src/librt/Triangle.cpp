//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
//
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"

// contructor
Triangle::Triangle(void)
        : Surface()
{
/*Equilateral triangle with length 1*/
    m_a = STVector3(1.0,0.0,0.0);
    m_b = STVector3(2.0,0.0,0.0);
    m_c = STVector3(1.0,2.0,0.0);
}


// clean up
Triangle::~Triangle()
{

}
void Triangle::
myTriangleTranslate(STVector3 A,STVector3 B, STVector3 C){
    m_a = A;
    m_b =B;
    m_c =C;
}

void Triangle::myTriangleRotate(){

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------
    //L.Run();
    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    STVector3 E1 = m_b - m_a;
    STVector3 E2 = m_c - m_a;
    STVector3 d = ray.Direction();
    STVector3 h = cross(d,E2);
    float a = dotp(E1,h);
    if (a > -0.00001 && a < 0.00001)
            return(false);
    float f =1 / a;
    STVector3 Rorg = ray.Origin();
    STVector3 s = Rorg - m_a;
    float u = f * (dotp(s,h));
    if( u< 0 || u >1.0)
        return false;
    STVector3 q = cross(s,E1);
    float v = f *(dotp(d,q));
    if(v <0.0 || u+v > 1.0)
        return false;
    float t = f * (dotp(E2,q));
    if(t> 0.00001){
        float xx = Rorg.x+t*(d.x);
        float yy = Rorg.y+t*(d.y);
        float zz = Rorg.z+t*(d.z);
        std::cout<< " Intersectionpoint "<< xx << " "<<yy <<"" <<zz<<std::endl;
        pIntersection->point = STVector3(xx,yy,zz);
        pIntersection->surface = this;
        pIntersection->normal =ComputeNormalVector();
        pIntersection->distanceSqu = t*t;
        bFound = true;
    }
    return(bFound);
}
/*bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    STVector3 AB = m_b - m_a;
    STVector3 CB = m_c - m_b;
    STVector3 Rdir= ray.Direction();
    STVector3 norm = cross(AB,CB); //ComputeNormalVector();
    STVector3 rayorg = ray.Origin();
    STVector3 RA = rayorg - m_a;
    float a = -dotp(RA,norm);
     std::cout<<"RA"<<RA.x << " "<<RA.y<< " "<<RA.z<<std::endl;
    std::cout<<"norm"<<norm.x << " "<<norm.y<< " "<<norm.z<<std::endl;
    std::cout<<"Raydir"<<Rdir.x << " "<<Rdir.y<< " "<<Rdir.z<<std::endl;
    //if( norm == 0)
      // std::cout<<"Degenerate triange "<<std::endl;
    STVector3 h = cross(Rdir,norm);
  //  double u1=0.0,v1=0.0,w1=0.0;
  //  bfound = IntersectionSolver(Ray,m_a,m_b,m_c,&u1,&v1,&w1);

    std::cout<<" Inside triange Findinter a"<<a<< std::endl;
    if (a > -0.00001 && a < 0.00001)// almost parallel no intersection
          return(false);

    float  ainv = 1/a;
    float u = ainv * dotp(RA ,h);
    if(u<0.0 || u>0.1)
        return false;
    STVector3 q = cross(rayorg,AB);
    float v = ainv * dotp(q,Rdir);
    if(v<0.0 || v>1.0)
        return false;
    float t = ainv * dotp(CB,q);
   std:: cout<<" Inside triange Findinter val t = "<<t<<std::endl;
    if(t> 0.00001){
        float xx = rayorg.x+t*(Rdir.x);
        float yy = rayorg.y+t*(Rdir.y);
        float zz = rayorg.z+t*(Rdir.z);
        std::cout<< " Intersectionpoint "<< xx << " "<<yy <<"" <<zz<<std::endl;
        pIntersection->point = STVector3(xx,yy,zz);
        pIntersection->surface = this;
        pIntersection->normal =norm;
        pIntersection->distanceSqu = t*t;
        bFound = true;
    }
    return(bFound);
}*/
float Triangle::dotp(const STVector3 &u, const STVector3 &v)
{
    return (u.x*v.x+u.y*v.y+u.z*v.z);
}

STVector3 Triangle:: operator += (const STVector3 &v)
{
    this->m_a.x+= v.x;
    this->m_b.y+= v.y;
    this->m_c.z+=v.z;
    return(STVector3(this->m_a.x ,this->m_b.y,this->m_c.z));
}
STVector3 Triangle:: operator -= (const STVector3 &v)
{
    this->m_a.x-= v.x;
    this->m_b.y-= v.y;
    this->m_c.z-=v.z;
    return(STVector3(this->m_a.x ,this->m_b.y,this->m_c.z));
}

STVector3 Triangle::cross(const STVector3 &u, const STVector3 &v)
{
   float xn = u.y*v.z -u.z*v.y;
   float yn = u.z*v.x - u.x*v.z;
   float zn= u.x*v.y- u.y*v.x;
   std::cout << "cross xn "<<xn<<" "<<yn<<" "<<zn<< std::endl;
   return STVector3(xn ,yn, zn);

  }

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------

    //---------------------------------------------------
    STVector3 CA = m_c - m_a;
    STVector3 BA = m_b - m_a;
    normal = cross(CA,BA);
    return(normal);
}


// TO DO: Proj2 raytracer
// CAP5705 - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
//
//---------------------------------------------------------
//---------------------------------------------------------
