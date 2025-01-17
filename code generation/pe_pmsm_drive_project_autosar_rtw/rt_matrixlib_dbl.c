/* Copyright 1994-2013 The MathWorks, Inc.
 *
 * File: rt_matrixlib_dbl.c
 *
 * Abstract:
 *      Simulink Coder utility functions
 *
 */

#include <math.h>
#include "rt_matrixlib.h"

#ifdef CREAL_T
void rt_ComplexTimes_Dbl(creal_T* c,
                         const creal_T a,
                         const creal_T b)
{
    if (a.im == 0.0) {
        c->re = a.re * b.re;
        c->im = a.re * b.im;
        if (b.im == 0.0) {
            c->im = 0.0;
        } else if (b.re == 0.0 || a.re == 0.0) {
            c->re = 0.0;
        }
    } else if (b.im == 0.0) {
        c->re = a.re * b.re;
        c->im = a.im * b.re;
        if (b.re == 0.0 || a.re == 0.0) { 
            c->re = 0.0;
        }
    } else if (a.re == 0.0) {
        c->re = -a.im * b.im;
        c->im = a.im * b.re;
        if (b.re == 0.0) {
            c->im = 0.0;
        }
    } else if (b.re == 0.0) {
        c->re = -a.im * b.im;
        c->im = a.re * b.im;
    } else {
        c->re = a.re * b.re - a.im * b.im;
        c->im = a.re * b.im + a.im * b.re;
    }
}

void rt_ComplexRDivide_Dbl(creal_T* c,
                           const creal_T a,
                           const creal_T b)
{
    if (b.im == 0.0) {
        c->re = a.re / b.re;
        if (a.im == 0.0) {
            c->im = 0.0;
        } else { /* a.im != 0.0 */
            c->im = a.im / b.re;
            if (a.re == 0.0) {
                c->re = 0.0;
            }
        }
    } else if (b.re == 0.0) { /* b.im != 0.0 */
        c->re = a.im / b.im;
        c->im = -a.re / b.im;
        if (a.re == 0.0) {
            c->im = 0.0;
        } else if (a.im == 0.0) {
            c->re = 0.0;
        }
    } else {
        float64 brm = fabs(b.re);
        float64 bim = fabs(b.im);
        if (brm > bim) {
            float64 s = b.im / b.re;
            float64 d = b.re + s * b.im;
            c->im = (a.im - s * a.re) / d;
            c->re = (a.re + s * a.im) / d;
        } else if (brm == bim) {
            float64 half = 0.5;
            float64 sgnbr = b.re > 0.0 ? half : -half;
            float64 sgnbi = b.im > 0.0 ? half : -half;
            c->im = (a.im*sgnbr - a.re*sgnbi)/brm;
            c->re = (a.re*sgnbr + a.im*sgnbi)/brm;
        } else {
            float64 s = b.re / b.im;
            float64 d = b.im + s * b.re;
            c->im = (s * a.im - a.re) / d;
            c->re = (s * a.re + a.im) / d;
        }
    }
}

void rt_ComplexReciprocal_Dbl(creal_T* Out,
                              const creal_T In1)
{
    creal_T y;
    y.re = 1.0;
    y.im = 0.0;

    rt_ComplexRDivide_Dbl(Out, y, In1);
}

#endif


float64 rt_Hypot_Dbl(float64 a, float64 b)
{
    float64 y;
    if (a != a || b != b) {
        y = a + b;
    } else {
        float64 t;
        if (fabs(a) > fabs(b)) {
            t = b/a;
            y = fabs(a)*sqrt(1.0 + t*t);
        } else {
            if (b == 0.0) {
                y = 0.0;
            } else {
                t = a/b;
                y = fabs(b)*sqrt(1.0 + t*t);
            }
        }
    }
    
    return y;
}
