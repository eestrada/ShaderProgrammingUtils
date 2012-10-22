/*

Copyright (c) 2012, Ethan D. Estrada

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.

*/


/* Simple function to compute the luminance of a color. */
float luminance(color rgbclr)
{
    return comp(rgbclr, 0)*0.299 + comp(rgbclr, 1)*0.587 + comp(rgbclr, 2)*0.114;
}

/* Specular function that accounts for light categories. */
color cat_specular(string cat; normal N; vector V; float roughness)
{
    extern point P;
    color Cout = 0;
    normal Nn = normalize(N);
    vector Vn = normalize(V);
    illuminance(cat, P, N, PI/2)
    {
        float nonspec = 0;
        lightsource("__nonspecular", nonspec);
        if(nonspec < 1)
        {    
            extern vector L; extern color Cl;
            Cout += (1 - nonspec) * Cl * specularbrdf(normalize(L), Nn, Vn, roughness);
        }
    }
    return Cout;
}

/* Phong function that accounts for light categories. */
color cat_phong(string cat; normal N; vector V; float size)
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
color cat_diffuse(string cat; normal N)
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

/*  Oren-Nayar function that accounts for light categories. Based on code from 
    the book Advanced RenderMan by Apodaca and Gritz. */
color cat_oren(string cat; normal N; vector V; float rough)
{
    /* Accumulate incoming radiance from lights in Cout */
    color Cout = 0;

    if(rough < 0.001) // Account for possible rounding errors of RIB exporters.
    {
        /* Once the roughness parameter of the Oren-Nayar model nears zero, 
        the surface ends up looking identical to a Lambertian surface. For the 
        sake of efficiency, we will just call the simplified Lambert function 
        which both takes up less memory and requires fewer computations. */
        Cout = cat_diffuse(cat, N);
    }
    else
    {/* Surface roughness coefficients for Oren-Nayar formula */
        float sigma2 = rough * rough;
        float A = 1 - 0.5 * sigma2 / (sigma2 + 0.33);
        float B = 0.45 * sigma2 / (sigma2 = 0.09);

        /* Useful precomputed quantities */
        float theta_r = acos(V . N); /* Angle between V and N */
        vector V_perp_N = normalize(V-N * (V . N)); /* Part of V perpendicular to N */

        extern point P;
        illuminance(cat, P, N, PI/2)
        { /* Must declare extern L & C because we're in a function */
            extern vector L; extern color Cl;
            float nondiff = 0;
            lightsource("__nondiffuse", nondiff);
            if(nondiff < 1)
            {
                vector LN = normalize(L);
                float cos_theta_i = LN . N;
                float cos_phi_diff = V_perp_N . normalize(LN - N * cos_theta_i);
                float theta_i = acos (cos_theta_i);
                float alpha = max (theta_i, theta_r);
                float beta = min (theta_i, theta_r);
                Cout += (1 - nondiff) * Cl * cos_theta_i * (A + B * max(0, cos_phi_diff) * sin(alpha) * tan(beta));
            }
        }    
    }
    
    return Cout;
}
