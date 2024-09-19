#include "VEC3.H"
#include <MATH.H>

vec3::vec3(): mX(0), mY(0), mZ(0) {}

vec3::vec3(float x, float y, float z): mX(x), mY(y), mZ(z) {}

vec3::vec3(const vec3& other) {
    mX = other.mX;
    mY = other.mY;
    mZ = other.mZ;
}

const vec3& vec3::operator=(const vec3& other) {
    mX = other.mX;
    mY = other.mY;
    mZ = other.mZ;

    return *this;
}

void vec3::sadd(float scalar) {
    mX += scalar;
    mY += scalar;
    mZ += scalar;
}

float vec3::len(void) {
    return sqrt(mX * mX + mY * mY + mZ * mZ);
}

void vec3::normalize(void) {
    float length = len();
    
    mX /= length;
    mY /= length;
    mZ /= length;
}

float vec3::dot(const vec3& other) {
    return mX * other.mX + mY * other.mY + mZ * other.mZ;

}

vec3 vec3::cross(const vec3& other) {
    vec3 result;

    result.x(mY * other.mZ - mZ * other.mY);
    result.y(mZ * other.mX - mX * other.mZ);
    result.z(mX * other.mY - mY * other.mX);

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
    mX += other.mX;
    mY += other.mY;
    mZ += other.mZ;

    return *this;
}

 vec3& vec3::operator-(const vec3 &other) { 
    mX -= other.mX;
    mY -= other.mY;
    mZ -= other.mZ;

    return *this;
}