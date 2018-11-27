typedef long long C; // could be long double
typedef complex<C> P; // represents a point or vector
#define X real()
#define Y imag()
...
P p = {4, 2}; // p.X = 4, p.Y = 2
P u = {3, 1};
P v = {2, 2};
P s = v+u; // {5, 3}
P a = {4, 2};
P b = {3, -1};
auto l = abs(b-a); // 3.16228
auto plr = polar(1.0, 0.5); // construct a vector of length 1 and angle 0.5 radians
v = {2, 2};
auto alpha = arg(v); // 0.463648
v *= plr; // rotates v by 0.5 radians counterclockwise. The length of plt must be 1 to rotate correctly.
auto beta = arg(v); // 0.963648
a = {4, 2};
b = {1, 2};
C p = (conj(a)*b).Y; // 6 <- the cross product of a and b