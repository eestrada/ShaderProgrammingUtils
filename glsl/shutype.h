/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#ifndef     __shutype_h__
#define     __shutype_h__

//define statements for common types
#define SHUint                  float
#define SHUfloat                float
#define SHUcolor                color
#define SHUnormal               normal
#define SHUpoint                point
#define SHUvector               vector
#define SHUvector4              <error>
#define SHUmatrix3              <error>
#define SHUmatrix4              matrix
#define SHUstring               string
/*  Maybe RSL will implement BSDFs someday, so just make this a float instead of
    an <error>.*/
#define SHUbsdf                 float    

#endif
