#ifndef VEC_H
#define VEC_H

#include <math.h>

//==================================================================================================

class vec
{
public:
    double x;
    double y;

    vec(double x_ = 0, double y_ = 0): x(x_), y(y_) {}
   ~vec() {x = NAN; y = NAN; }

    friend vec  operator + (const vec &main, const vec &add);
    friend vec &operator +=(      vec &main, const vec &add);

    friend vec  operator - (const vec &main, const vec &sub);
    friend vec &operator -=(      vec &main, const vec &sub);
    friend vec  operator - (const vec &main);

    friend vec  operator * (const double k, const vec &main);
    friend vec &operator *=(vec &main, const double k);

    friend vec  operator / (const vec &main, const double k);
    friend vec &operator /=(      vec &main, const double k);

    // Возвращает вектор, коллинеарный данному, длины len
    friend vec  operator | (const vec &main, const double len);
    friend vec &operator |=(      vec &main, const double len);

    // Возвращает вектор, повернутый на deg градусов отн-но исходного
    friend vec  operator ^ (const vec &main, const double deg);
    friend vec &operator ^=(      vec &main, const double deg);

    // Возвращает вектор, нормальный к данному, той же длины
    friend vec operator !(const vec &main);

    // Возвращает длину вектора
    friend double operator ~(const vec &main);

    // Возвращает скалярное произведение двух векторов
    friend double operator ,(const vec &v_1, const vec &v_2);
};

//==================================================================================================

inline vec  operator + (const vec &main, const vec &add) { return vec(main.x + add.x, main.y + add.y); }
inline vec &operator +=(      vec &main, const vec &add) { return main = main + add; }

inline vec  operator - (const vec &main, const vec &sub) { return vec(main.x - sub.x, main.y - sub.y); }
inline vec &operator -=(      vec &main, const vec &sub) { return main = main - sub; }
inline vec  operator - (const vec &main)                 { return -1.0 * main; }

inline vec  operator * (const double k, const vec &main) { return vec(k * main.x, k * main.y); }
inline vec &operator *=(vec &main, const double k)       { return main = k * main; }

inline vec  operator / (const vec &main, const double k) { return vec(main.x / k, main.y / k); }
inline vec &operator /=(      vec &main, const double k) { return main = main / k; }

inline vec  operator | (const vec &main, const double len) { return len * (main / ~main); }
inline vec &operator |=(      vec &main, const double len) { return main = main | len; }

inline vec    operator !(const vec &main)                { return vec(-main.y, main.x); }
inline double operator ~(const vec &main)                { return sqrt(main.x * main.x + main.y * main.y); }
inline double operator ,(const vec &v_1, const vec &v_2) { return v_1.x * v_2.x + v_1.y * v_2.y; }

#endif // VEC_H
