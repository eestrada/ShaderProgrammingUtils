float luminance(color rgbclr)
{
    return comp(rgbclr, 0)*0.299 + comp(rgbclr, 1)*0.587 + comp(rgbclr, 2)*0.114;
}

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

color cat_phong(normal N; vector V; float size)
{
    color Cout = 0;
    vector R = reflect(normalize(V),normalize(N));
        illuminance(P,N,PI/2)
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


color cat_oren(string cat; normal N; vector V; float rough)
{
    /* Accumulate incoming radiance from lights in Cout */
    color Cout = 0;

    if(rough != 0)
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
    else
    {
        Cout = cat_diffuse(cat, N);
    }
    return Cout;
}
