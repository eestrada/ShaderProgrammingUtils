/* 
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 */

#ifndef     __shutype_h__
#define     __shutype_h__

//define statements for common types
#define SHUint                  int
#define SHUfloat                float
#define SHUcolor                vector
#define SHUnormal               vector
#define SHUpoint                vector
#define SHUvector               vector
#define SHUvector4              vector4
#define SHUmatrix3              matrix3
#define SHUmatrix4              matrix
#define SHUstring               string
#define SHUbsdf                 bsdf

//How to declare types
#define SHUint_cast(i)               ((int)(i))
#define SHUfloat_cast(f)             ((float)(f))
#define SHUcolor_cast(r,g,b)         {r,g,b}
#define SHUnormal_cast(x,y,z)        {x,y,z}
#define SHUpoint_cast(x,y,z)         {x,y,z}
#define SHUvector_cast(x,y,z)        {x,y,z}
#define SHUvector4_cast(x,y,z,w)     {x,y,z,w}
#define SHUbsdf_cast(x)              bsdf(x)

#endif
