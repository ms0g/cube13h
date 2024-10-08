#include "TRINGL.H"

vec3 computeNormal(vec3* vertices) {
    vec3 a = vertices[0];
    vec3 b = vertices[1];
    vec3 c = vertices[2];

    vec3 ac = c - a;
    normalize(ac);

    vec3 ab = b - a;
    normalize(ab);
        
    vec3 normal = cross(ab, ac);
    normalize(normal);

    return normal;
}
