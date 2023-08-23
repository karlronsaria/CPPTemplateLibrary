#include "Complex.h"

template <typename T>
const Complex<T> Complex<T>::Im = Complex<T>{ (T)0, (T)1 };

/*
    cos(x) = (1/2)(e(ix) + e(-ix))
    cos(ix) = (1/2)(e(-x) + e(x))

    sin(x) = (1/2i)(e(ix) + e(-ix))
    sin(ix) = -(1/2)(e(-x) - e(x))i

    cos(a + bi) = cos a cos bi - sin a sin bi
    cos(a + bi) = cos a (1/2)(e(-b) + e(b)) + sin a (1/2)(e(-b) - e(b)) i
    cos(a + bi) = (1/2)( cos a (e(-b) + e(b)), sin a (e(-b) - e(b)) )
*/
complex_t cos(const complex_t& z) {
    return 0.5L * complex_t(
        cos(z.re()) * (exp(-z.im()) + exp(z.im())),
        sin(z.re()) * (exp(-z.im()) - exp(z.im()))
    );
}

/*
    cos(x) = (1/2)(e(ix) + e(-ix))
    cos(ix) = (1/2)(e(-x) + e(x))

    sin(x) = (1/2i)(e(ix) + e(-ix))
    sin(ix) = -(1/2)(e(-x) - e(x))i

    sin(a + bi) = sin a cos bi + cos a sin bi
    sin(a + bi) = sin a (1/2)(e(-b) + e(b)) - cos a (1/2)(e(-b) - e(b)) i
    sin(a + bi) = (1/2)( sin a (e(-b) + e(b)), cos a (e(b) - e(-b)) )
*/
complex_t sin(const complex_t& z) {
    return 0.5L * complex_t(
         sin(z.re()) * (exp(z.im()) + exp(-z.im())),
         cos(z.re()) * (exp(z.im()) - exp(-z.im()))
    );
}

complex_t tan(const complex_t& z) {
    return sin(z) / cos(z);
}

/*
    Note
        T = arccos(x) means cos(T) = x
        T = arccos(z) means cos(T) = z

    Then
        cos(T) = z
        (1/2)(e(iT) + e(-iT)) = z
        e(iT) + e(-iT) = 2z
        e(iT) + e(-iT) - 2z = 0
        e(2iT) + e(iT - iT) - (2z)e(iT) = 0
        e(2iT) + 1 - (2z)e(iT) = 0
        e(2iT) - (2z)e(iT) + 1 = 0

    Let
        u = e(iT)

    Then
        u^2 - (2z)u + 1 = 0

    Then
        u = (1/2)(2z +- sqrt(4z^2 - 4))
        u = (1/2)(2z +- 2 sqrt(z^2 - 1))
        u = z +- sqrt(z^2 - 1)
        u = z +- (z^2 - 1)^(1/2)

    Then
        e(iT) = z +- sqrt(z^2 - 1)
        T = -i ln( z +- sqrt(z^2 - 1) )

        arccos(z) = -i ln( z +- sqrt(z^2 - 1) )

        Arccos(z) = -i ln( z + sqrt(z^2 - 1) )
*/
complex_t acos(const complex_t& z) {
    return -complex_t::Im * log(z + sqrt(z * z - 1));
}

/*
    T = arcsin(z) means sin(T) = z

    sin(T) = z
    (1/2i)(e(iT) - e(-iT)) = z
    e(iT) - e(-iT) - 2iz = 0
    e(2iT) - 1 - (2iz)e(iT) = 0
    e(2iT) - (2iz)e(iT) - 1 = 0

    e(iT) = (1/2)(2iz +- sqrt(-4z^2 + 4))
    e(iT) = (1/2)(2iz +- 2 sqrt(1 - z^2))
    e(iT) = iz +- sqrt(1 - z^2)
    T = -i ln(iz +- sqrt(1 - z^2))

    arcsin(z) = -i ln(iz +- sqrt(1 - z^2))

    Arcsin(z) = -i ln(iz + sqrt(1 - z^2))
*/
complex_t asin(const complex_t& z) {
    return -complex_t::Im * log(complex_t::Im * z + sqrt(1.L - z * z));
}

/*
    arctan(z) = T means tan(T) = z

    tan(T) = z

    sin(T) / cos(T) = z
    (e(iT) - e(-iT)) / i(e(iT) + e(-iT)) = z
    e(iT)(e(iT) - e(-iT)) / e(iT)i(e(iT) + e(-iT)) = z
    (e(2iT) - 1) / i(e(2iT) + 1) = z
    (e(2iT) - 1) / (e(2iT) + 1) = iz
    e(2iT) - 1 = iz (e(2iT) + 1)
    e(2iT) - 1 = (iz)e(2iT) + iz
    e(2iT) - (iz)e(2iT) = iz + 1
    e(2iT)(1 - iz) = iz + 1
    e(2iT) = (iz + 1)/(1 - iz)
    e(2iT) = (iz + (-1)(-1))/((-1)(-1) - iz)
    e(2iT) = (iz + ii(-1))/(ii(-1) - iz)
    e(2iT) = (z - i)/(-i - z)
    e(2iT) = (i - z)/(i + z)
    2iT = ln( (i - z)/(i + z) )
    T = (1/2i) ln( (i - z)/(i + z) )

    arctan(z) = (1/2i) ln( (i - z)/(i + z) )
*/
complex_t atan(const complex_t& z) {
    return -0.5L * complex_t::Im * log((complex_t::Im - z) / (complex_t::Im + z));
}

complex_t cosh(const complex_t& z) {
    return 0.5L * (exp(z) + exp(-z));
}

complex_t sinh(const complex_t& z) {
    return 0.5L * (exp(z) - exp(-z));
}

complex_t tanh(const complex_t& z) {
    return (exp(z) - exp(-z)) / (exp(z) + exp(-z));
}

/*
    e(T) = z +- sqrt(z^2 - 1)
    T = ln( z +- sqrt(z^2 - 1) )
    Arccosh(z) = ln( z + sqrt(z^2 - 1) )
*/
complex_t acosh(const complex_t& z) {
    return log(z + sqrt(z * z - 1));
}

/*
    e(T) = z +- sqrt(1 - z^2)
    T = ln(z +- sqrt(1 - z^2))
    Arcsin(z) = ln(z + sqrt(1 - z^2))
*/
complex_t asinh(const complex_t& z) {
    return log(z + sqrt(1.L - z * z));
}

/*
    e(2T) = (z + 1)/(1 - z)
    e(2T) = (1 + z)/(1 - z)
    T = (1/2) ln( (1 + z)/(1 - z) )

    arctanh(z) = (1/2) ln( (1 + z)/(1 - z) )
*/
complex_t atanh(const complex_t& z) {
    return 0.5L * log((1.L + z) / (1.L - z));
}

complex_t cis(flt_t a) {
    return complex_t{ cos(a), sin(a) };
}

complex_t cis(const complex_t& z) {
    return cos(z) + complex_t::Im * sin(z);
}

/*
    exp(a + bi)
        = exp(a) exp(bi)
        = exp(a)( cos(b) + i sin(b) )
*/
complex_t exp(const complex_t& z) {
    return TO_FLT(exp(z.re())) * cis(z.im());
}

/*
    Suppose
        a + bi = ln(z)

    Then
        exp(a + bi) = z
        exp(a) exp(bi) = z
        exp(a) exp(bi) = abs(z) exp(i arg(z))

    Then
        exp(a) = abs(z)
        a = ln(abs(z))
        b = arg(z)
*/
complex_t log(const complex_t& z) {
    return complex_t{ log(abs(z)), arg(z) };
}

flt_t abs(const complex_t& z) {
    return sqrt(z.re() * z.re() + z.im() * z.im());
}

/*
    arg(a + bi) = {
        with t = atan(abs(b) / abs(a)) :
            t : a > 0 and b > 0,
            pi - t : a < 0 and b > 0,
            pi + t : a < 0 and b < 0,
            2pi - t : a > 0 and b < 0
    }
*/
flt_t arg(const complex_t& z) {
    if (z.re() == 0) {
        if (z.im() > 0)
            return PI / 2;

        return 3 * PI / 2;
    }

    flt_t Arg = atan(fabs(z.im()) / fabs(z.re()));

    if (z.re() > 0) {
        if (z.im() > 0)
            return Arg;

        return 2 * PI - Arg;
    }

    if (z.im() > 0) {
        return PI - Arg;
    }

    return PI + Arg;
}

complex_t pow(const complex_t& z, int_t c) {
    complex_t temp(1.L, 0.L);

    for (int i = 0; i < c; ++i)
        temp *= z;

    return temp;
}

/*
    a^w = a^(c + di)
        = a^c a^(di)
        = a^c exp(di ln a)
        = a^c (cos(d ln a) + i sin(d ln a))
*/
complex_t pow(flt_t a, const complex_t& w) {
    return TO_FLT(pow(a, w.re())) * cis(w.im() * log(a));
}

/*
    z^w = z^(c + di)
        = z^c z^(di)
        = z^c (cos(d ln z) + i sin(d ln z))
*/
complex_t pow(const complex_t& z, const complex_t& w) {
    return fpow(z, w.re()) * cis(w.im() * log(z));
}

/*
    (a + bi)^n
        = (abs(a + bi) * e(i arg(a + bi)))^n
        = abs^n (a + bi) * e(i n arg(a + bi))
        = abs^n (a + bi) * ( cos(n arg(a + bi)) + i sin(n arg(a + bi)) )
        = abs^n (a + bi) * ( cos(n arg(a + bi)), sin(n arg(a + bi)) )
*/
complex_t fpow(const complex_t& z, flt_t c) {
    return TO_FLT(pow(abs(z), c)) * cis(c * arg(z));
}

flt_t sq_sum(const complex_t& z) {
    return z.re() * z.re() + z.im() * z.im();
}

complex_t sqrt(const complex_t& z) {
    return fpow(z, 0.5L);
}
