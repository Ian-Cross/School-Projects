
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "random.h"
#include "sphere.h"

#include <float.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <omp.h>
#include <time.h>

#define IR 0
#define IG 1
#define IB 2

vec3 color(const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}


hittable *random_scene() {
    int n = 500;
    hittable **list = new hittable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                        center, 0.2,
                        new lambertian(vec3(random_double()*random_double(),
                                            random_double()*random_double(),
                                            random_double()*random_double()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                        center, 0.2,
                        new metal(vec3(0.5*(1 + random_double()),
                                       0.5*(1 + random_double()),
                                       0.5*(1 + random_double())),
                                  0.5*random_double())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hittable_list(list,i);
}

int main(int argc, char *argv[]) {
    int argPtr;
    int thread_count = 1;
    int output_flag = 0;
    int image_width = 640;
    int image_height = 480;
    std::ofstream outputFile;

    if (argc > 1) {
        argPtr = 1;
        while (argPtr < argc) {
            if (strcmp(argv[argPtr], "-thread") == 0) {
                sscanf(argv[argPtr + 1], "%d", &thread_count);
                argPtr += 2;
            } else if (strcmp(argv[argPtr], "-output") == 0) {
                output_flag = 1;
                argPtr += 1;
            } else if (strcmp(argv[argPtr], "-size") == 0) {
                sscanf(argv[argPtr + 1], "%d", &image_width);
                sscanf(argv[argPtr + 2], "%d", &image_height);
                argPtr += 3;
            } else {
                printf("USAGE: %s <-thread thread_count> <-output> <-size xWidth yHeight>\n", argv[0]);
                printf(" thread_count -the number of threads to use during processing\n");
                printf(" -output -whether or not to save the output in an external file\n");
                printf(" xWidth yHeight -the width and height of the image produced\n");
                exit(1);
            }
        }
    }

    if (output_flag) {
        outputFile.open ("image.ppm");
        outputFile << "P3\n" << image_width << " " << image_height << "\n255\n";
    }

    int ns = 10;
    time_t start_time, end_time;
    hittable *world = random_scene();

    time(&start_time);

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int imageOutput[image_height*image_width][3];
    int i,j;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(image_width)/float(image_height), aperture, dist_to_focus);

    omp_set_dynamic(0);
    omp_set_num_threads(thread_count);

    #pragma omp parallel for shared(imageOutput,j,i) collapse(2)
    for (j = image_height-1; j >= 0; j--) {
        for ( i = 0; i < image_width; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + random_double()) / float(image_width);
                float v = float(j + random_double()) / float(image_height);
                ray r = cam.get_ray(u, v);
                col += color(r, world,0);
            }
            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            imageOutput[j*image_width + i][IR] = int(255.99*col[0]);
            imageOutput[j*image_width + i][IG] = int(255.99*col[1]);
            imageOutput[j*image_width + i][IB] = int(255.99*col[2]);
        }
    }

    time(&end_time);

    if (output_flag == 1) {
        for (int j = image_height*image_width - 1; j >= 0 ; j--)
            outputFile << imageOutput[j][IR] << " " << imageOutput[j][IG] << " " << imageOutput[j][IB] << "\n";
        outputFile.close();
    } else {
      std::cout << difftime(end_time,start_time) << "\n";
    }

    return 0;
}
