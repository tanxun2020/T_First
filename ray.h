#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray{
public:
    point3 orig;
    vec3 dir;
    double mint, maxt, t;
public:
    ray(){}
    ray(const point3& origin, const vec3& direction, double mint = 0, double maxt = 100)
        : orig(origin), dir(direction), mint(mint), maxt(maxt), t(50.0)
    {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at() const{
        return orig + t * dir;
    }
    point3 at(double tb) const{
        return orig + tb * dir;
    }
};


#endif // RAY_H
