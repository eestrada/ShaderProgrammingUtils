/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#include "shumath.h"
#include "shupattern.h"
#include "shusurf.h"
#include "shutype.h"

surface
testsurf()
{
    color testclr = shu_specular("", normalize(N), normalize(I), 0.1);
    Ci = testclr;
}
