/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#ifndef     __shupattern_h__
#define     __shupattern_h__

// Map common noise types
#define MAP_NOISE_FUNCTIONS(type)   \
type shu_noise(float f) \
    { return type noise(f); } \
type shu_noise(float ss, tt) \
    { return type noise(ss,tt); } \
type shu_noise(point pt) \
    { return type noise(pt); } \
type shu_noise(point pt; float tt) \
    { return type noise(pt,tt); } \
type shu_snoise(float f) \
    { return (2*(type noise(f))-1); } \
type shu_snoise(float ss, tt) \
    { return (2*(type noise(ss,tt))-1); } \
type shu_snoise(point pt) \
    { return (2*(type noise(pt))-1); } \
type shu_snoise(point pt; float tt) \
    { return (2*(type noise(pt,tt))-1); } \
type shu_cellnoise(float f) \
    { return type cellnoise(f); } \
type shu_cellnoise(float ss, tt) \
    { return type cellnoise(ss,tt); } \
type shu_cellnoise(point pt) \
    { return type cellnoise(pt); } \
type shu_cellnoise(point pt; float tt) \
    { return type cellnoise(pt,tt); } \

MAP_NOISE_FUNCTIONS(float)
MAP_NOISE_FUNCTIONS(color)
MAP_NOISE_FUNCTIONS(point)
MAP_NOISE_FUNCTIONS(vector)

#endif
