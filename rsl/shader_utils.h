/* 
 *
 * Copyright (C) 2012, Ethan D. Estrada
 *
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 * 
 */


/* Simple function to compute the luminance of a color. */
float su_luminance(color rgbclr)
{
    return comp(rgbclr, 0)*0.299 + comp(rgbclr, 1)*0.587 + comp(rgbclr, 2)*0.114;
}

/* Specular function that accounts for light categories. */
color su_specular(string cat; normal N; vector V; float roughness)
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
color su_phong(string cat; normal N; vector V; float size)
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
color su_diffuse(string cat; normal N)
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
color su_orennayar(string cat; normal N; vector V; float rough)
{
    color Cout = 0;

    if(rough < 0.0001) // Account for possible rounding errors of RIB exporters.
    {
        /* Once the roughness nears zero, use a lambert since it is cheaper */
        Cout = su_diffuse(cat, N);
    }
    else
    {
        /* Not yet implemented. */
    }
    
    return Cout;
}
