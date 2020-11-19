#include "BitmapPlusPlus.hpp"
#include "vec3.h"
#include "ray.h"
#include "TriangleMesh.h"
#include "LoadObject.h"
#include "Hit_Result.h"
#include <omp.h>
#include <iostream>

static int count = 0;

bool Result(ray &r, const std::shared_ptr<TriangleMesh> &tMesh,int &fid, uv &uv_){
    int nFace = tMesh->nTriangles;
    double tmin = r.t;
    int j;
    uv temp_uv;
    #pragma omp parallel for
    for(int i = 0; i < nFace; ++i){
        Triangle Tri_tmp(tMesh, i);
        if(Tri_tmp.Inersect(r, temp_uv)){
            if(r.t < tmin){
                tmin = r.t;
                uv_ = temp_uv;
                j = i;
            }
        }
        count += 1;
    }
    if(tmin != 50.0){
        Triangle T(tMesh,j);
        fid = j;
        return true;
    }
    else {
        return false;
    }
}


bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

color ray_color(ray& r,const std::shared_ptr<TriangleMesh> &tMesh){
    uv uv;
    int fid;
    if (Result(r, tMesh, fid, uv)){

        int tn1 = tMesh->vertexIndices[fid].n1;
        int tn2 = tMesh->vertexIndices[fid].n2;
        int tn3 = tMesh->vertexIndices[fid].n3;

        vec3 n1 = tMesh->n[tn1];
        vec3 n2 = tMesh->n[tn2];
        vec3 n3 = tMesh->n[tn3];

        color c = (1 - uv.u - uv.v) * n1 + uv.u * n2 + uv.v * n3;
        return 0.5 * color(c.x +1, c.y +1, c.z +1);
    }
   // cout << "0" << endl;
    color unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(void){
    omp_set_num_threads(52);
    //TriangleMesh m();
    const auto aspect_ratio = 16.0/9.0;
    const int w = 512;
    const int h = static_cast<int>(w / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    LoadObject p("pig.obj");
    std::shared_ptr<TriangleMesh> Tmesh(new TriangleMesh(p.nFace, p.nPoint, p.nVer, p.fArray, p.pArray, p.nArray));
    //output image
    #pragma omp parallel for
    for(int i = 0; i < 10000; ++i){
        printf("i = %d, I am Thread %d\n", i, omp_get_thread_num());
    }
/*    for (std::int32_t y = 0; y < h; ++y){
        for (std::int32_t x = 0; x < w; ++x){
            auto u = double(x) / (w-1);
            auto v = double(y) / (h-1);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r, Tmesh);
        }
    }
    try{
        bmp::Bitmap image(w, h);
        #pragma omp parallel for
        for (std::int32_t y = 0; y < image.Height(); ++y){
            for (std::int32_t x = 0; x < image.Width(); ++x){
                auto u = double(x) / (image.Width()-1);
                auto v = double(y) / (image.Height()-1);

                ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
                color pixel_color = ray_color(r, Tmesh);
                bmp::Pixel color = {
                    static_cast<std::uint8_t>(255.999 * pixel_color.x),
                    static_cast<std::uint8_t>(255.999 * pixel_color.y),
                    static_cast<std::uint8_t>(255.999 * pixel_color.z)
                };
                image.Set(x,image.Height() - y -1, color);
            }
        }
        image.Save("image9.bmp");
    }
    catch (const bmp::BitmapException& e){
        std::cerr << "[BMP ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }*/
    LoadObject p2("box.obj");
    for(int i = 0; i < p2.nPoint; ++i){
        cout << i << ":" << p2.pArray[i] << endl;
    }
    cout << "count : " << count << endl;
    cout << "nface : " << Tmesh->nTriangles << endl;
    return EXIT_SUCCESS;
}
