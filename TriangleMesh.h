#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <iostream>
#include <vector>
#include <memory>
#include "ray.h"
#include "LoadObject.h"
#include "vec3.h"

//using namespace std;
struct uv{
    uv():u(0),v(0){}
    double u,v;
};


struct TriangleMesh {
    explicit TriangleMesh(int nTriangles, int npoint,
                 int nVertices, const face3 *verIndices,
                 const point3 *P, const vec3 *N)
        : nTriangles(nTriangles),
          nVertices(nVertices){
     // Copy _P_N_ vertex data, if present

        p.reset(new point3[npoint]);
        for(int i = 0; i < npoint; ++i) p[i] = P[i];

        n.reset(new vec3[nVertices]);
        for(int i = 0; i < nVertices; ++i) n[i] = N[i];

        vertexIndices.reset(new face3[nTriangles]);
        for(int i = 0; i < nTriangles; ++i) vertexIndices[i] = verIndices[i];

        //vertexIndices.reset(new face3[nTriangles]);
        //for(int i = 0; i < nVertices; ++i) vertexIndices[i] = verIndices[i];
    }
    const int nTriangles, nVertices;
    std::unique_ptr<face3[]> vertexIndices;
    std::unique_ptr<point3[]> p;
    std::unique_ptr<vec3[]> n;
};

class Triangle{
public:
    explicit Triangle(const std::shared_ptr<TriangleMesh> &mesh, int triNumber):
        mesh(mesh),
        primIndex(triNumber){
        t = &mesh->vertexIndices[triNumber];//3 vertes in Triangle for vector array
    }
    bool Inersect(ray &ray,uv &uv) const{

        vec3 &p1 = mesh->p[t->v1];
        vec3 &p2 = mesh->p[t->v2];
        vec3 &p3 = mesh->p[t->v3];

//        vec3 &n1 = mesh->n[t->n1];
//       vec3 &n2 = mesh->n[t->n2];
//        vec3 &n3 = mesh->n[t->n3];
        //cout << t->v1 << "  mmmm  "  << t->v2 << "  mmmm  " << t->v3 << endl;
        //cout << p1 << "  mmmm  "  << p2 << "  mmmm  " << p3 << endl;
        vec3 e1 = p2 - p1;
        vec3 e2 = p3 - p1;
        vec3 s1 = cross(ray.dir,e2);
        //cout << s1 << "mmmm"  << e1 << "mmmm" << e2 << endl;
        double divisor = dot(s1, e1);
        //cout << divisor << endl;
        if(divisor == 0.f) return false;
        double invDivisor = 1.0f / divisor;
        //cout << invDivisor << endl;
        // Compute first barycentric coordinate
        vec3 s = ray.origin() - p1;
        double b1 = dot(s, s1) * invDivisor;
        //cout << b1 << endl;
        if(b1 < 0.0f || b1 > 1.0f) return false;
        //cout << b1 << endl;
        // Compute second barycentric coordinate
        vec3 s2 = cross(s,e1);
        double b2 = dot(ray.dir,s2) * invDivisor;
        if(b2 < 0.0f || b1 + b2 > 1.0f) return false;
        //cout << b2 << endl;
        // Compute _t_ to intersection point
        //cout << s2 << "  mmmm  "  << e2 << "  mmmm  " << invDivisor << endl;
        //cout << invDivisor << endl;
        double t = dot(e2, s2) * invDivisor;
        //cout << t << endl;
        if(t < ray.mint || t > ray.maxt) return false;
        //cout << t << endl;
        ray.t = t;
        uv.u = b1;
        uv.v = b2;
        return true;
    }
    const std::shared_ptr<TriangleMesh> mesh;
    const face3 *t;
    const int primIndex;
};

#endif // TRIANGLEMESH_H
