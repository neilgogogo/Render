//
//  sphere.h
//  Render
//
//  Created by Neil Li on 2020/4/22.
//  Copyright © 2020 Neil Li. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

class sphere: public hittable {
    public:
        sphere() {}
        sphere(vec3 cen, double r, shared_ptr<material> m)
                   : center(cen), radius(r), mat_ptr(m) {};
        //构造函数，定义圆的原点，半径，和材质

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
        
        bool bounding_box(double t0, double t1, aabb& output_box) const {
            output_box = aabb(
                center - vec3(radius, radius, radius),
                center + vec3(radius, radius, radius));
            return true;
        }
        
        void get_sphere_uv(const vec3& p, double& u, double& v) {
            auto phi = atan2(p.z(), p.x());
            auto theta = asin(p.y());
            u = 1-(phi + pi) / (2*pi);
            v = (theta + pi/2) / pi;
        }

    public:
        vec3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif /* sphere_h */
