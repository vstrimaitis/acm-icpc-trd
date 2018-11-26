template <typename T>
struct Vec {
    T x, y;
    Vec(): x(0), y(0) {}
    Vec(T _x, T _y): x(_x), y(_y) {}
    Vec operator+(const Vec& b) {
        return Vec<T>(x+b.x, y+b.y);
    }
    Vec operator-(const Vec& b) {
        return Vec<T>(x-b.x, y-b.y);
    }
    Vec operator*(T c) {
        return Vec(x*c, y*c);
    }
    T operator*(const Vec& b) {
        return x*b.x + y*b.y;
    }
    T operator^(const Vec& b) {
        return x*b.y-y*b.x;
    }
    bool operator<(const Vec& other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    bool operator==(const Vec& other) const {
        return x==other.x && y==other.y;
    }
    bool operator!=(const Vec& other) const {
        return !(*this == other);
    }
    friend ostream& operator<<(ostream& out, const Vec& v) {
        return out << "(" << v.x << ", " << v.y << ")";
    }
    friend istream& operator>>(istream& in, Vec<T>& v) {
        return in >> v.x >> v.y;
    }
    T norm() { // squared length
        return (*this)*(*this);
    }
    ld len() {
        return sqrt(norm());
    }
    ld angle(const Vec& other) { // angle between this and other vector
        return acosl((*this)*other/len()/other.len());
    }
};
/* Cross product of 3d vectors: (ay*bz-az*by, az*bx-ax*bz, ax*by-ay*bx)
 */