//
//  hittable.h
//  Render
//
//  Created by Neil Li on 2020/4/22.
//  Copyright © 2020 Neil Li. All rights reserved.
//

#ifndef hittable_h
#define hittable_h

#include "ray.h"
#include "aabb.h"

class material;

struct hit_record {
    vec3 p;
    vec3 normal;
    
    shared_ptr<material> mat_ptr;
    double t;
    double u;//U,V surface coordinates of the ray-object hit point,about texture
    double v;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const = 0;
};
#endif /* hittable_h */
