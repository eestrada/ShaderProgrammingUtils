CC = aqsl#$(SHADERC)
RENDER = aqsis
CFLAGS = -I inc/
OUT := shaders/superlight.slx shaders/superSurface.slx

shaders : $(OUT)

shaders/%.slx : src/%.sl
	@- mkdir -p shaders/
	- $(CC) $(CFLAGS) -o $@ $<

rib :
	$(RENDER) rib/sphere.rib

clean :
	-rm -rf shaders/
