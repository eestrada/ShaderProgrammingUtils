ShaderProgrammingUtils
======================

ShaderProgrammingUtils is a repository of header files with shader programming specific functions for various shading languages.

The header files for each of the languages should contain the same functions. And these functions should more or less act the same. This should make it fairly simple to write shaders in different languages that act similarly in different renderers. There will be cases where it doesn't make sense or isn't possible to define functions that act the same in all respects. For instance, RSL does not have a concept of a BSDF of radiance closure; or at least not in the same way that VEX and OSL do. Thus functions that return a BSDF in other languages will return a float value of 0 for RSL.

Except where code is noted to be from another source, this software is placed in the public domain and is provided as is without express or implied warranty.
