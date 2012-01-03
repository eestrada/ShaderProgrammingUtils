#include "shader_utils.h"

surface superSurface()
{
	color diffclr = cat_diffuse("", N) * Cs;
	color ambclr = ambient() * Cs;
    Oi = Os;
    Ci = (diffclr + ambclr) * Oi;
}
