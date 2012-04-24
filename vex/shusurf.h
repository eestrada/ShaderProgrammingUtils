/* 
 * Except where code is noted to be from another source, this software is 
 * placed in the public domain and is provided as is without express or implied 
 * warranty. 
 */

#ifndef     __shusurf_h__
#define     __shusurf_h__

#include "shumath.h"

/* lighting model BRDFs */

#define shu_specularBRDF(nL,nN,nV,rough)    specularBRDF(nL, nN, nV, rough)
#define shu_phongBRDF(nL,nN,nV,rough)       phongBRDF(nL, nN, nV, rough)
#define shu_blinnBRDF(nL,nN,nV,rough)       blinnBRDF(nL, nN, nV, rough)
#define shu_diffuseBRDF(nL,nN,nV,rough)     diffuseBRDF(nL, nN, nV, rough)
#define shu_diffuseBRDF(nL,nN)              diffuseBRDF(nL, nN)
#define shu_diffuseBRDF                     diffuseBRDF

/* lighting model BSDFs */

#define shu_specularBSDF(vector nN; float exponent) \
    matchvex_specular(vector nN; float exponent)
#define shu_specularBSDF(float exponent) \
    matchvex_specular(float exponent)
#define shu_specularBSDF matchvex_specular

bsdf shu_phongBSDF(vector nN; float exponent)
    { return bsdf(phong(nN, exponent)); }

bsdf shu_phongBSDF(float exponent)
    { return bsdf(phong(exponent)); }

bsdf shu_blinnBSDF(vector nN; float exponent)
    { return bsdf(blinn(nN, exponent)); }

bsdf shu_blinnBSDF(float exponent)
    { return bsdf(blinn(exponent)); }

bsdf shu_diffuseBSDF(vector nN; float rough)
    { return bsdf(diffuse(nN, rough)); }

bsdf shu_diffuseBSDF(vector nN)
    { return bsdf(diffuse(nN)); }

bsdf shu_diffuseBSDF()
    { return bsdf(diffuse()); }

/* Various Surface model functions that sample all lights via an illuminance
    loop. All have support for categories. */

// Renderer specific specular with light categories
vector shu_specular(string cat; vector nN; vector nI; float roughness)
{
    vector Cout = 0.0f;
    illuminance(P, nN, SHU_PI_2, bouncemask("specular"), "categories", cat)
    {
        Cout += shadow(Cl) * shu_specularBRDF(shu_normalize(L), nN, nI, roughness);
    }
    return Cout;
}

// Renderer specific specular
vector shu_specular(vector nN; vector nI; float roughness)
{
    return shu_specular("", nN, nI, roughness);
}

// Blinn-Phong specular with light categories
vector shu_blinn(string cat; vector nN; vector nI; float roughness)
{
    vector Cout = 0.0f;
    illuminance(P, nN, SHU_PI_2, bouncemask("specular"), "categories", cat)
    {
        Cout += shadow(Cl) * shu_blinnBRDF(shu_normalize(L), nN, nI, roughness);
    }
    return Cout;
}

// Blinn-Phong specular
vector shu_blinn(vector nN; vector nI; float roughness)
{
    return shu_blinn("", nN, nI, roughness);
}

// Phong specular with light categories
vector shu_phong(string cat; vector nN; vector nI; float roughness)
{
    vector Cout = 0.0f;
    illuminance(P, nN, SHU_PI_2, bouncemask("specular"), "categories", cat)
    {
        Cout += shadow(Cl) * shu_phongBRDF(shu_normalize(L), nN, nI, roughness);
    }
    return Cout;
}

// Phong specular
vector shu_phong(vector nN; vector nI; float roughness)
{
    return shu_phong("", nN, nI, roughness);
}

// Oren-Nayar diffuse with light categories
vector shu_diffuse(string cat; vector nN; vector nI; float roughness)
{
    vector Cout = 0.0f;
    float Kdiff = 0.0f;

    illuminance(P, nN, SHU_PI_2, bouncemask("specular"), "categories", cat)
    {
        if(roughness > 0)
            {Kdiff = shu_diffuseBRDF(shu_normalize(L), nN, nI, roughness);}
        else
            {Kdiff = shu_diffuseBRDF(shu_normalize(L), nN);}
        Cout += shadow(Cl) * Kdiff;
    }
    return Cout;
}

// Oren-Nayar diffuse
vector shu_diffuse(vector nN; vector nI; float roughness)
{
    return shu_diffuse("", nN, nI, roughness);
}

// Lambertian diffuse with light categories
vector shu_diffuse(string cat; vector nN)
{
    vector Cout = 0.0f;
    illuminance(P, nN, SHU_PI_2, bouncemask("specular"), "categories", cat)
    {
        Cout += shadow(Cl) * shu_diffuseBRDF(shu_normalize(L), nN);
    }
    return Cout;
}

// Lambertian diffuse
vector shu_diffuse(vector nN)
{
    return shu_diffuse("", nN);
}

#endif
