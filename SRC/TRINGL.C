#include "TRINGL.H"

vec3 computeNormal(vec3* vertices) {
    vec3 ab, ac, normal;
    vec3 a = vertices[0];
    vec3 b = vertices[1];
    vec3 c = vertices[2];

    ac = sub(&c, &a);
    normalize(&ac);

    ab = sub(&b, &a);
    normalize(&ab);
        
    normal = cross(&ab, &ac);
    normalize(&normal);

    return normal;
}
