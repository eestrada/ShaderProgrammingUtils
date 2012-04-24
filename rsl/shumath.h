/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#ifndef     __shumath_h__
#define     __shumath_h__

#define SHU_E           2.71828
#define SHU_PI          3.14159
#define SHU_PI_2        1.57079


//Define common math function
#define shu_pow             pow
#define shu_abs             abs
#define shu_exp             exp
#define shu_log             log
#define shu_sqrt            sqrt
#define shu_floor           floor
#define shu_ceil            ceil
#define shu_min             min
#define shu_max             max
#define shu_clamp           clamp
#define shu_mix             lerp
#define shu_smooth          smooth
#define shu_mod(a,b)        ((a)%(b))

//Define geometric functions
#define shu_length          length
#define shu_distance(a,b)   shu_length(a-b)
#define shu_dot(a,b)        ((a).(b))
#define shu_cross           cross
#define shu_normalize       normalize
#define shu_faceforward     frontface
#define shu_reflect         reflect
#define shu_refract         refract

//Define angle and trigonometry function words
#define shu_radians         radians
#define shu_degrees         degrees
#define shu_sin             sin
#define shu_cos             cos
#define shu_tan             tan
#define shu_asin            asin
#define shu_acos            acos
#define shu_atan            atan
#define shu_sinh            sinh
#define shu_cosh            cosh
#define shu_tanh            tanh
#define shu_asinh           asinh
#define shu_acosh           acosh
#define shu_atanh           atanh


//Define color functions
float shu_luminance(color rgbclr)
{
    return comp(rgbclr, 0)*0.299+comp(rgbclr, 1)*0.587+comp(rgbclr, 2)*0.114;
}

#endif
