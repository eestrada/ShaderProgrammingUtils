/* 
 *
 * Copyright (C) 2012, Ethan D. Estrada
 *
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 * 
 */

#ifndef     __shader_utils_h__
#define     __shader_utils_h__

//define statements for common types
#define SHUfloat    float
#define SHUcolor    vector
#define SHUnormal   vector
#define SHUpoint    vector
#define SHUvector   vector
#define SHUstring   string
#define SHUbsdf     bsdf

//Since only Houdini/Mantra uses VEX, we'll use these Houdini header files
#include <math.h>
#include <shading.h>

/* Simple function to compute the luminance of a color. */
SHUfloat shu_luminance(SHUcolor rgbclr)
{
    return comp(rgbclr, 0)*0.299 + comp(rgbclr, 1)*0.587 + comp(rgbclr, 2)*0.114;
}

/* light model BRDFs */

SHUfloat shu_specularBRDF(SHUvector nL;SHUnormal nN;SHUvector nV;SHUfloat rough)
{
    return specularBRDF(nL, nN, nV, rough);
}


/* Specular function that accounts for light categories. */
SHUcolor shu_specular(string cat; SHUnormal nN; SHUvector nI; SHUfloat roughness)
{
    SHUcolor Cout = 0;
    illuminance(cat, P, nN, M_PI/2, SPECULAR_LIGHTS)
    {
        Cout += Cl * SHUspecularbrdf(normalize(L), nN, nI, roughness);
    }
    return Cout;
}

/* Phong function that accounts for light categories. */
color shu_phong(string cat; normal N; vector V; float size)
{
    color Cout = 0;
    vector R = reflect(normalize(V),normalize(N));
        illuminance(cat, P, N, PI/2)
        {
            extern vector L; extern color Cl;
            
            float nonspec = 0;
            lightsource("__nonspecular", nonspec);
            if(nonspec < 1)
            {
                vector Ln = normalize(L);
                Cout += (1 - nonspec) * Cl * pow(max(0.0,R.Ln),size);
            }
        }
    return Cout;
}

/* Lambert function that accounts for light categories. */
color shu_diffuse(string cat; normal N)
{
    extern point P;
    color Cout = 0;
    normal Nn = normalize(N);
    illuminance(cat, P, N, PI/2)
    {
        float nondiff = 0;
        lightsource("__nondiffuse", nondiff);
        if(nondiff < 1)
        {
            extern vector L; extern color Cl;
            vector Ln = normalize(L);
            Cout += (1 - nondiff) * Cl * Ln.Nn;
        }
    }
    return Cout;
}

/* Oren-Nayar function that accounts for light categories. */
color shu_orennayar(string cat; normal N; vector V; float rough)
{
    color Cout = 0;

    if(rough < 0.0001) // Account for possible rounding errors of RIB exporters.
    {
        /* Once the roughness nears zero, use a lambert since it is cheaper */
        Cout = shu_diffuse(cat, N);
    }
    else
    {
        /* Not yet implemented. */
    }
    
    return Cout;
}

#endif
