#include "VEC.H"
#include <math.h>
#include "MATH.H"

vec3::vec3(): mX(0), mY(0), mZ(0) {}

vec3::vec3(float x, float y, float z): mX(x), mY(y), mZ(z) {}

vec3::vec3(const vec3& other) {
    mX = other.x();
    mY = other.y();
    mZ = other.z();
}

const vec3& vec3::operator=(const vec3& other) {
    mX = other.x();
    mY = other.y();
    mZ = other.z();

    return *this;
}

void vec3::sadd(float scalar) {
    mX += scalar;
    mY += scalar;
    mZ += scalar;
}

float vec3::invLen(void) {
    return invSqrt(mX * mX + mY * mY + mZ * mZ);
}

void vec3::normalize(void) {
    float length = invLen();
    
    mX *= length;
    mY *= length;
    mZ *= length;
}

float vec3::dot(const vec3& v) {
    return (mX * v.x()) + (mY * v.y()) + (mZ * v.z());

}

vec3 vec3::cross(const vec3& v) {
    vec3 result;

    result.x(mY * v.z() - mZ * v.y());
    result.y(mZ * v.x() - mX * v.z());
    result.z(mX * v.y() - mY * v.x());

    return result;
}

vec2 vec3::project(int fov) {
    vec2 result = {
        (fov * mX) / mZ,
        (fov * mY) / mZ
    };

    return result;
}

vec3 vec3::rotx(float angle) {
    vec3 result;

    result.x(mX);
    result.y(mY * cos(angle) - mZ * sin(angle));
    result.z(mY * sin(angle) + mZ * cos(angle));
   
    return result;
}
vec3 vec3::roty(float angle) {
    vec3 result;

    result.x(mX * cos(angle) - mZ * sin(angle));
    result.y(mY);
    result.z(mX * sin(angle) + mZ * cos(angle));
   
    return result;
}
vec3 vec3::rotz(float angle) {
    vec3 result;

    result.x(mX * cos(angle) - mY * sin(angle));
    result.y(mX * sin(angle) + mY * cos(angle));
    result.z(mZ);
   
    return result;
}

 vec3& vec3::operator+(const vec3 &other) { 
    mX += other.x();
    mY += other.y();
    mZ += other.z();

    return *this;
}

 vec3& vec3::operator-(const vec3 &other) { 
    mX -= other.x();
    mY -= other.y();
    mZ -= other.z();

    return *this;
}