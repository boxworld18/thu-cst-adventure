#ifndef VECIO_H
#define VECIO_H

#include <ostream>
#include <istream>
#include <vecmath.h>

std::ostream& operator<<(std::ostream& os, const Vector2f& v);
std::ostream& operator<<(std::ostream& os, const Vector3f& v);

std::ostream& operator<<(std::ostream& os, const Matrix3f& v);
std::ostream& operator<<(std::ostream& os, const Matrix4f& v);

#endif //VECIO_H
