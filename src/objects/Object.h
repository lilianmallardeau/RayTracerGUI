//
// Created by lilian on 06/01/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include "../include/utils.h"
#include "../environment/Ray.h"
#include "../environment/Light.h"

class Scene;

/**
 * Base class for objects
 */
class Object {
    public:
        /** Material of the object */
        Material matter;

        /** Name of the object */
        std::string name;

    public:
        Object() : matter(Material()) {};

        /**
         * Checks if a ray hit the object
         * @param ray the ray to check if it intersects the object
         * @return true if the ray hit the object, false otherwise
         */
        virtual bool is_hit(Ray ray) = 0;

        /**
         * Computes the intersection point between a ray and the object
         * @param ray ray to compute the intersection point with
         * @pre is_hit(ray) == true
         * @return the intersection point between the ray and the object
         */
        virtual Point3D get_intersect(Ray ray) = 0;

        /**
         * Computes the normal vector of the object at the intersection point between the ray and the object
         * @param ray
         * @pre is_hit(ray) == true
         * @return the normal vector at the intersection point between the object and the ray
         */
        virtual Vector3D get_normal(Ray ray) = 0;

        /**
         * Computes the distance between the ray origin and the intersection point with the object
         * @param ray
         * @pre is_hit(ray) == true
         * @return the distance between the ray origin and the intersection point
         */
        float compute_hit_dist(Ray ray);

        /**
         * Computes the reflected ray on the object
         * @param ray
         * @pre is_hit(ray) == true
         * @return the reflected ray on the object
         */
        virtual Ray reflect(Ray ray);

        /**
         * Computes the color of the pixel corresponding to a ray
         * @param ray
         * @param scene the scene with all the objects
         * @param depth the current number of reflexions
         * @pre is_hit(ray) == true
         * @return the computed color with the Phong relation
         */
        Color compute_color(Ray ray, Scene & scene, unsigned int depth);

        /**
         * Getter for the shininess of the object
         * @return the shininess of the object
         */
        float getShininess();

        /**
         * Getter for the color of the object
         * @return the color of the object
         */
        Color getColor();

        /**
         * Setter for the shininess of the object
         * @param s new shininess of the object
         */
        void setShininess(float s);

        /**
         * Setter for the color of the object
         * @param c new color of the object
         */
        void setColor(Color c);
};


#endif //RAYTRACER_OBJECT_H
