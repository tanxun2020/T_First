#ifndef LOADOBJECT_H
#define LOADOBJECT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include "vec3.h"
using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;

struct face3{
    face3():v1(0),v2(0),v3(0),
        n1(0),n2(0),n3(0){}
    int v1, v2, v3;
    int n1, n2, n3;
};

class LoadObject {
public:
    LoadObject(const string FilePath){
        vector<point3> p;
        vector<vec3> n;
        vector<face3> f;
        ifstream openFile;
        openFile.open(FilePath);
        string sl;

        while (getline(openFile,sl)) {
            if(sl[0] == 'v'){
                if(sl[1] == ' '){
                    istringstream in(sl);
                    string head;
                    point3 tp;
                    in >> head >> tp.x >> tp.y >> tp.z;
                    p.push_back(tp);
                }
                else{
                    istringstream in(sl);
                    string head;
                    vec3 tn;
                    in >> head >> tn.x >> tn.y >> tn.z;
                    n.push_back(tn);
                }
            }
            else if(sl[0] == 'f'){
                for(int i = 0; i < static_cast<int>(sl.size()); ++i){
                    if(sl[i] == '/') sl[i] = ' ';
                }
                istringstream in(sl);
                string head;
                face3 face;
                in >> head >> face.v1 >> face.n1
                        >> face.v2 >> face.n2
                        >> face.v3 >> face.n3;
                face.v1--;
                face.v2--;
                face.v3--;
                face.n1--;
                face.n2--;
                face.n3--;
                f.push_back(face);
            }
        }

        nPoint = static_cast<int>(p.size());
        nVer = static_cast<int>(n.size());
        nFace = static_cast<int>(f.size());

        pArray = new point3[nPoint];
        for(int i = 0; i < nPoint; ++i) pArray[i] = p[i];

        nArray = new vec3[nVer];
        for(int i = 0; i < nVer; ++i) nArray[i] = n[i];

        fArray = new face3[nFace];
        for(int i = 0; i < nFace; ++i) fArray[i] = f[i];
    }
    ~LoadObject(){
        delete []pArray;
        delete []nArray;
        delete []fArray;
    };
public:
    int nPoint, nVer, nFace;
    point3 *pArray;
    vec3 *nArray;
    face3 *fArray;
};





#endif // LOADOBJECT_H
