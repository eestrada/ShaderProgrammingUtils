light
superlight (
      point from = point "shader" (0,0,0);
      point to = point "shader" (1,0,0);
      string lighttype = "point";
      color lightcolor = 1;
      float doshadows = 1;
      float samples = 1;
      float coneangle = 45;
      float conedelta = 10;
      float conefalloff = 1;
      float lightradius = 0.01;
      output float __nondiffuse = 0;
      output float __nonspecular = 0)
{
	uniform float DEGTORAD = 0.0174532925;
	/* Convert degrees to radians. */
	uniform float radangle = coneangle * DEGTORAD;
	uniform float raddelta = conedelta * DEGTORAD;
	
	if(lighttype == "point")
	{
		illuminate( from )
		{
			if(doshadows)
 	  		{
 	  			//Cl = transmission(Ps, from, "samples", samples, "samplecone", lightradius) * lightcolor;
 	  		}
	   		else
	   		{
	   			Cl = lightcolor;
	   		}
		}
	}
	else if(lighttype == "spotlight")
	{
		illuminate( from, vector((to - from) / length(to - from)), radangle + raddelta )
		{
			if(doshadows)
 	  		{
 	  			//Cl = transmission(Ps, from, "samples", samples, "samplecone", lightradius) * lightcolor;
 	  		}
	   		else
	   		{
	   			Cl = lightcolor;
	   		}
		}
	}
}
