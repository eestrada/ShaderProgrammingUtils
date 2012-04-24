/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#ifndef     __shusurf_h__
#define     __shusurf_h__

#include "shumath.h"

/* lighting model BRDFs */

#define shu_specularBRDF(nL,nN,nV,rough)    specularbrdf(nL, nN, nV, rough)

float shu_phongBRDF(vector nL; normal nN; vector nV; float rough)
{
    vector R = shu_reflect(-nV, nN);
    return shu_pow(shu_max(0, shu_dot(R,nL)), rough);
}

float shu_blinnBRDF(vector nL; normal nN; vector nV; float rough)
{
    vector nH = shu_normalize(nL+nV);
    return shu_pow(shu_max(0, shu_dot(nH,nN)), rough);
}

float shu_diffuseBRDF(vector nL; normal nN)
    {return shu_dot(nL,nN);}

// This isn't implemented yet so just use the function above
float shu_diffuseBRDF(vector nL; normal nN; vector nV; float rough)
    {return shu_diffuseBRDF(nL,nN);}

/* lighting model BSDFs */
/* RSL has no concept of a BSDF or a radiance closure, so these return 0. */
float shu_specularBSDF(vector nN; float exponent)   {return 0;}
float shu_specularBSDF(float exponent)              {return 0;}
float shu_phongBSDF(vector nN; float exponent)      {return 0;}
float shu_phongBSDF(float exponent)                 {return 0;}
float shu_blinnBSDF(vector nN; float exponent)      {return 0;}
float shu_blinnBSDF(float exponent)                 {return 0;}
float shu_diffuseBSDF(vector nN; float rough)       {return 0;}
float shu_diffuseBSDF(vector nN)                    {return 0;}
float shu_diffuseBSDF()                             {return 0;}


/* Various Surface model functions that sample all lights via an illuminance
    loop. All have support for categories. */

// Renderer specific specular with light categories
color shu_specular(string cat; vector nN; vector nI; float roughness)
{
    color Cout = 0;
    float nonspec;
    extern point P;
    illuminance(cat, P, nN, SHU_PI_2)
    {
        extern vector L; extern color Cl;
        nonspec = 0;
        lightsource("__nonspecular", nonspec);

        if(nonspec < 1)
        {
            Cout += Cl * shu_specularBRDF(shu_normalize(L), nN, nI, roughness);
        }
    }
    return Cout;
}

// Renderer specific specular
color shu_specular(vector nN; vector nI; float roughness)
{
    return specular(nN, nI, roughness);
}

// Blinn-Phong specular with light categories
color shu_blinn(string cat; vector nN; vector nI; float roughness)
{
    color Cout = 0;
    float nonspec;
    extern point P;
    illuminance(cat, P, nN, SHU_PI_2)
    {
        extern vector L; extern color Cl;
        nonspec = 0;
        lightsource("__nonspecular", nonspec);

        if(nonspec < 1)
        {
            Cout += Cl * shu_blinnBRDF(shu_normalize(L), nN, nI, roughness);
        }
    }
    return Cout;
}

// Blinn-Phong specular
color shu_blinn(vector nN; vector nI; float roughness)
{
    return shu_blinn("", nN, nI, roughness);
}

// Phong specular with light categories
color shu_phong(string cat; vector nN; vector nI; float roughness)
{
    color Cout = 0;
    float nonspec;
    
    extern point P;
    illuminance(cat, P, nN, SHU_PI_2)
    {
        extern vector L; extern color Cl;
        nonspec = 0;
        lightsource("__nonspecular", nonspec);

        if(nonspec < 1)
        {
            Cout += Cl * shu_phongBRDF(shu_normalize(L), nN, nI, roughness);
        }
    }
    return Cout;
}

// Phong specular
color shu_phong(vector nN; vector nI; float roughness)
{
    return phong(nN, nI, roughness);
}

// Oren-Nayar diffuse with light categories
color shu_diffuse(string cat; vector nN; vector nI; float roughness)
{
    color Cout = 0;
    float nondiff, Kdiff = 0;
    extern point P;
    illuminance(cat, P, nN, SHU_PI_2)
    {
        extern vector L; extern color Cl;
        nondiff = 0;
        lightsource("__nondiffuse", nondiff);
        
        if(nondiff < 1)
        {
            if(roughness > 0)
                {Kdiff = shu_diffuseBRDF(shu_normalize(L), nN, nI, roughness);}
            else
                {Kdiff = shu_diffuseBRDF(shu_normalize(L), nN);}
            Cout += Cl * Kdiff;
        }
    }
    return Cout;
}

// Oren-Nayar diffuse
color shu_diffuse(vector nN; vector nI; float roughness)
{
    return shu_diffuse("", nN, nI, roughness);
}

// Lambertian diffuse with light categories
color shu_diffuse(string cat; vector nN)
{
    color Cout = 0;
    extern point P;
    illuminance(cat, P, nN, SHU_PI_2)
    {
        extern vector L; extern color Cl;
        Cout += Cl * shu_diffuseBRDF(shu_normalize(L), nN);
    }
    return Cout;
}

// Lambertian diffuse
color shu_diffuse(vector nN)
{
    return diffuse(nN);
}

#endif
