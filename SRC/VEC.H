#ifndef VEC_H
#define VEC_H
 
struct vec2 {
    float x;
    float y;
};

class vec3 {
public:
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec3& other);
    const vec3& operator=(const vec3& other);

    inline float x(void) const { return mX; }
    inline float y(void) const { return mY; }
    inline float z(void) const { return mZ; }
    
    inline void x(float v) { mX = v; }
    inline void y(float v) { mY = v; }
    inline void z(float v) { mZ = v; }

    void sadd(float scalar);
    float len(void);
    void normalize(void);
    float dot(const vec3& v);
    vec3 cross(const vec3& v);
    vec2 project(int fov);

    vec3 rotx(float angle);
    vec3 roty(float angle);
    vec3 rotz(float angle);
    
    vec3& operator+(const vec3 &other);
    vec3& operator-(const vec3 &other);

private:
    float mX;
    float mY;
    float mZ;  
};

#endif