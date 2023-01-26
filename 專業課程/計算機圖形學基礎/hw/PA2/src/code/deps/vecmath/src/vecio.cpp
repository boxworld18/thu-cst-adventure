#include <vecio.h>

std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
    os << v[0] << ' ' << v[1];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
    os << v[0] << ' ' << v[1] << ' ' << v[2];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix3f& m) {
    os << m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << '\n'
       << m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << '\n'
       << m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix4f& m) {
    os << m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << ' ' << m(0, 3) << '\n'
       << m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << ' ' << m(1, 3) << '\n'
       << m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << ' ' << m(2, 3) << '\n'
       << m(3, 0) << ' ' << m(3, 1) << ' ' << m(3, 2) << ' ' << m(3, 3) << '\n';
    return os;
}
