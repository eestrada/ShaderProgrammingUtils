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
    { return type(noise(f)); } \
type shu_noise(float ss, tt) \
    { return type(noise(ss,tt)); } \
type shu_noise(vector pt) \
    { return type(noise(pt)); } \
type shu_noise(vector pt; float tt) \
    { return type(noise(set(pt[0],pt[1],pt[2],tt))); } \
type shu_snoise(float f) \
    { return (2*(type(noise(f)))-1); } \
type shu_snoise(float ss, tt) \
    { return (2*(type(noise(ss,tt)))-1); } \
type shu_snoise(vector pt) \
    { return (2*(type(noise(pt)))-1); } \
type shu_snoise(vector pt; float tt) \
    { return (2*(type(noise(set(pt[0],pt[1],pt[2],tt))))-1); } \
type shu_cellnoise(float f) \
    { return type(noise(f)); } \
type shu_cellnoise(float ss, tt) \
    { return type(noise(ss,tt)); } \
type shu_cellnoise(vector pt) \
    { return type(noise(pt)); } \
type shu_cellnoise(vector pt; float tt) \
    { return type(noise(set(pt[0],pt[1],pt[2],tt))); } \

MAP_NOISE_FUNCTIONS(float)
MAP_NOISE_FUNCTIONS(vector)

#endif
