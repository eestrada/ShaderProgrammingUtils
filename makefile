CC = $(SHADERC)
CFLAGS = -I inc/
OUT = shaders/superlight.$(SLEXT)

shaders : $(OUT)

shaders/%$(SLEXT) : src/%.sl
	mkdir -p shaders/
	$(SHADERC) $(CFLAGS) -o $@ $<
