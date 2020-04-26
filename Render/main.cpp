//
//  main.cpp
//  Render
//
//  Created by Neil Li on 2020/4/22.
//  Copyright © 2020 Neil Li. All rights reserved.
//

//#include <iostream>
//#include <fstream>
//#include "vec3.h"
//#include "ray.h"
//using namespace std;
//vec3 ray_color(const ray& r) {
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//}
//bool hit_sphere(const vec3& center, double radius, const ray& r) {
//    vec3 oc = r.origin() - center;
//    auto a = dot(r.direction(), r.direction());
//    auto b = 2.0 * dot(oc, r.direction());
//    auto c = dot(oc, oc) - radius*radius;
//    auto discriminant = b*b - 4*a*c;
//    return (discriminant > 0);
//}
//double hit_sphere(const vec3& center, double radius, const ray& r) {
//    vec3 oc = r.origin() - center;
//    auto a = dot(r.direction(), r.direction());
//    auto b = 2.0 * dot(oc, r.direction());
//    auto c = dot(oc, oc) - radius*radius;
//    auto discriminant = b*b - 4*a*c;
//    if (discriminant < 0) {
//        return -1.0;
//    } else {
//        return (-b - sqrt(discriminant) ) / (2.0*a);
//    }
//}

//vec3 ray_color(const ray& r) {
//    if (hit_sphere(vec3(0,0,-1), 0.5, r))
//        return vec3(1, 0, 0);
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//}
//vec3 ray_color(const ray& r) {
//    auto t = hit_sphere(vec3(0,0,-1), 0.5, r);
//    //圆内部
//    if (t > 0.0) {
//        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
//        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
//    }
//    vec3 unit_direction = unit_vector(r.direction());
//    t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//    //return vec3(0,0,0);
//}
//
//int main() {
    //输出梯度图
//    const int image_width = 200;
//    const int image_height = 100;
//    ofstream OutImage;
//    OutImage.open("Image.ppm");
//    OutImage << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//    for (int j = image_height-1; j >= 0; --j) {
//        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//        for (int i = 0; i < image_width; ++i) {
//            auto r = double(i) / image_width;
//            auto g = double(j) / image_height;
//            auto b = 0.2;
//            int ir = static_cast<int>(255.999 * r);
//            int ig = static_cast<int>(255.999 * g);
//            int ib = static_cast<int>(255.999 * b);
//            OutImage << ir << ' ' << ig << ' ' << ib << '\n';
//        }
//    }
    //构造
//        const int image_width = 200;
//        const int image_height = 100;
//
//        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//        for (int j = image_height-1; j >= 0; --j) {
//            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//            for (int i = 0; i < image_width; ++i) {
//                vec3 color(double(i)/image_width, double(j)/image_height, 0.2);
//                color.write_color(std::cout);
//            }
//        }
//
//        std::cerr << "\nDone.\n";
    
  
//        const int image_width = 200;
//        const int image_height = 100;
//
//        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
//        vec3 lower_left_corner(-2.0, -1.0, -1.0);
//        vec3 horizontal(4.0, 0.0, 0.0);
//        vec3 vertical(0.0, 2.0, 0.0);
//        vec3 origin(0.0, 0.0, 0.0);
//
//        ofstream OutImage;
//        OutImage.open("Image1.ppm");
//        OutImage << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//        for (int j = image_height-1; j >= 0; --j) {
//            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//            for (int i = 0; i < image_width; ++i) {
//                auto u = double(i) / image_width;
//                auto v = double(j) / image_height;
//                ray r(origin, lower_left_corner + u*horizontal + v*vertical);
//                vec3 color = ray_color(r);
//
//                color.write_image(OutImage);
//
//
//
//            }
//        }
//
//        std::cerr << "\nDone.\n";
//
//}

#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camera.h"
#include "moving_sphere.h"
#include <iostream>
#include <fstream>


//vec3 ray_color(const ray& r, const hittable& world) {
//    hit_record rec;
//    if (world.hit(r, 0, infinity, rec)) {
//        //return 0.5 * (rec.normal + vec3(1,1,1));
//        return 0.5*(rec.normal + vec3(1,1,1));
//    }
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//}

vec3 ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {

//        vec3 target = rec.p + rec.normal + random_unit_vector();
//        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);

        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return vec3(0,0,0);

    }


    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
//
//int main() {
//    const int image_width = 200;
//    const int image_height = 100;
//    const int samples_per_pixel = 100;
//    const int max_depth = 50;
//    const auto aspect_ratio = double(image_width) / image_height;
//
//    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//    vec3 lower_left_corner(-2.0, -1.0, -1.0);
//    vec3 horizontal(4.0, 0.0, 0.0);
//    vec3 vertical(0.0, 2.0, 0.0);
//    vec3 origin(0.0, 0.0, 0.0);
//    std::ofstream OutImage;
//    OutImage.open("Image11.ppm");
//    OutImage << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//
////    hittable_list world;
////    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
////    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));
//
//    hittable_list world;
//
////    world.add(make_shared<sphere>(
////        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.7, 0.3, 0.3))));
////
////    world.add(make_shared<sphere>(
////        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
////
////    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2))));
////    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.8, 0.8))));
//
//    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));
//    world.add(make_shared<sphere>(
//        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
//    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3)));
//    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
//    world.add(make_shared<sphere>(vec3(-1,0,-1), -0.45, make_shared<dielectric>(1.5)));
//
//
//    //camera properties
//    vec3 lookfrom(3,3,2);
//    vec3 lookat(0,0,-1);
//    vec3 vup(0,1,0);
//    auto dist_to_focus = (lookfrom-lookat).length();
//    auto aperture = 2.0;
//    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
//
//
//
//    for (int j = image_height-1; j >= 0; --j) {
//        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//        for (int i = 0; i < image_width; ++i) {
////            auto u = double(i) / image_width;
////            auto v = double(j) / image_height;
////            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
////
////            vec3 color = ray_color(r, world);
////
////            color.write_image(OutImage);
//
//            vec3 color(0, 0, 0);
//            for (int s = 0; s < samples_per_pixel; ++s) {
//                auto u = (i + random_double()) / image_width;
//                auto v = (j + random_double()) / image_height;
//                ray r = cam.get_ray(u, v);
//
//                color += ray_color(r, world, max_depth);
//             }
//            //color.write_color(std::cout, samples_per_pixel);
//            color.write_image(OutImage, samples_per_pixel);
//        }
//    }
//
//    std::cerr << "\nDone.\n";
//
//}


hittable_list random_scene() {
    hittable_list world;
    
    auto checker = make_shared<checker_texture>(
        make_shared<constant_texture>(vec3(0.2, 0.3, 0.1)),
        make_shared<constant_texture>(vec3(0.9, 0.9, 0.9))
    );

    world.add(make_shared<sphere>(vec3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
//                if (choose_mat < 0.8) {
//                    // diffuse
//                    auto albedo = vec3::random() * vec3::random();
//                    world.add(
//                        make_shared<sphere>(center, 0.2, make_shared<lambertian>(albedo)));
//                }
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    world.add(make_shared<moving_sphere>(
                        center, center + vec3(0, random_double(0,.5), 0), 0.0, 1.0, 0.2,
                        make_shared<lambertian>(make_shared<constant_texture>(albedo))));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                        make_shared<sphere>(center, 0.2, make_shared<metal>(albedo, fuzz)));
                } else {
                    // glass
                    world.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    world.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));

    world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(make_shared<constant_texture>(vec3(1, 0.2, 0.1)))));
        
    
    
    
    world.add(
        make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

int main() {
    
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const auto aspect_ratio = double(image_width) / image_height;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    std::ofstream OutImage;
    OutImage.open("Image15.ppm");
    OutImage << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    auto world = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus,0.0,1.0);
    
    for (int j = image_height-1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
    //            auto u = double(i) / image_width;
    //            auto v = double(j) / image_height;
    //            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
    //
    //            vec3 color = ray_color(r, world);
    //
    //            color.write_image(OutImage);
    
                vec3 color(0, 0, 0); //新建一个vec3.color向量
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / image_width;
                    auto v = (j + random_double()) / image_height;
                    ray r = cam.get_ray(u, v);
    
                    color += ray_color(r, world, max_depth);
                 }
                //color.write_color(std::cout, samples_per_pixel);
                color.write_image(OutImage, samples_per_pixel);
            }
        }
    
        std::cerr << "\nDone.\n";
    
}
