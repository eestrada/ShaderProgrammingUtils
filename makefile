CC = $(SHADERC)
CFLAGS = -I inc/
EXT = $(SLEXT)
OUT = shaders/superlight.$(EXT)

shaders : $(OUT)

shaders/%$(SLEXT) : src/%.sl
	mkdir -p shaders/
	$(CC) $(CFLAGS) -o $@ $<
