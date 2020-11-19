#ifndef HIT_RESULT_H
#define HIT_RESULT_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "vec3.h"
#include "TriangleMesh.h"
#include "LoadObject.h"
#include "ray.h"


/*bool Result(const ray &r, const std::shared_ptr<TriangleMesh> &tMesh, Triangle &Tri, double &dis, double tmax){
    int nFace = tMesh->nTriangles;
    double tmin = tmax;
    int j;
    for(int i = 0; i < nFace; ++i){
        Triangle Tri_tmp(tMesh, i);
        if(Tri_tmp.Inersect(r)){
            if(r.t < tmin){
                tmin = r.t;
                j = i;
            }
        }
    }
    if(tmin != tmax){
        Triangle T(tMesh,j);
        Tri = T;
        dis = tmin;
        return true;
    }
    else {
        return false;
    }
}*/



#endif // HIT_RESULT_H
