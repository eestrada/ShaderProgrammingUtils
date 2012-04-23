/* 
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 */

#ifndef     __shusurf_h__
#define     __shusurf_h__

/* lighting model BRDFs */

float shu_specularBRDF(vector nL;vector nN;vector nV;float rough)
{
    return specularBRDF(nL, nN, nV, rough);
}

float shu_phongBRDF(vector nL;vector nN;vector nV;float rough)
{
    return phongBRDF(nL, nN, nV, rough);
}

float shu_blinnBRDF(vector nL;vector nN;vector nV;float rough)
{
    return blinnBRDF(nL, nN, nV, rough);
}

float shu_diffuseBRDF(vector nL;vector nN;vector nV;float rough)
{
    return diffuseBRDF(nL, nN, nV, rough);
}

float shu_diffuseBRDF(vector nL;vector nN)
{
    return diffuseBRDF(nL, nN);
}

/* lighting model BSDFs */

bsdf shu_specularBSDF(vector nN; float exponent)
{
    return matchvex_specular(nN, exponent);
}

bsdf shu_specularBSDF(float exponent)
{
    return matchvex_specular(exponent);
}

bsdf shu_phongBSDF(vector nN; float exponent)
{
    return bsdf(phong(nN, exponent));
}

bsdf shu_phongBSDF(float exponent)
{
    return bsdf(phong(exponent));
}

bsdf shu_blinnBSDF(vector nN; float exponent)
{
    return matchvex_blinn(nN, exponent);
}

bsdf shu_blinnBSDF(float exponent)
{
    return matchvex_blinn(exponent);
}

bsdf shu_diffuseBSDF(vector nN; float rough)
{
    return bsdf(diffuse(nN, rough));
}

bsdf shu_diffuseBSDF(vector nN)
{
    return bsdf(diffuse(nN));
}

bsdf shu_diffuseBSDF()
{
    return bsdf(diffuse());
}

/* Specular function that accounts for light categories. */
vector shu_specular(string cat; vector nN; vector nI; float roughness)
{
    vector Cout = 0;
    illuminance(P, nN, M_PI/2, bouncemask("specular"), "categories", cat)
    {
        Cout += Cl * shu_specularBRDF(normalize(L), nN, nI, roughness);
    }
    return Cout;
}

#endif
