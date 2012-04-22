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
    return rgbclr[0]*0.299 + rgbclr[1]*0.587 + rgbclr[2]*0.114;
}

/* light model BRDFs */

SHUfloat shu_specularBRDF(SHUvector nL;SHUnormal nN;SHUvector nV;SHUfloat rough)
{
    return specularBRDF(nL, nN, nV, rough);
}

SHUfloat shu_phongBRDF(SHUvector nL;SHUnormal nN;SHUvector nV;SHUfloat rough)
{
    return phongBRDF(nL, nN, nV, rough);
}

SHUfloat shu_blinnBRDF(SHUvector nL;SHUnormal nN;SHUvector nV;SHUfloat rough)
{
    return blinnBRDF(nL, nN, nV, rough);
}

SHUfloat shu_diffuseBRDF(SHUvector nL;SHUnormal nN;SHUvector nV;SHUfloat rough)
{
    return diffuseBRDF(nL, nN, nV, rough);
}

SHUfloat shu_diffuseBRDF(SHUvector nL;SHUnormal nN)
{
    return diffuseBRDF(nL, nN);
}

/* Specular function that accounts for light categories. */
SHUcolor shu_specular(string cat; SHUnormal nN; SHUvector nI; SHUfloat roughness)
{
    SHUcolor Cout = 0;
    illuminance(P, nN, M_PI/2, SPECULAR_LIGHTS)
    {
        Cout += Cl * SHUspecularbrdf(normalize(L), nN, nI, roughness);
    }
    return Cout;
}

#endif
