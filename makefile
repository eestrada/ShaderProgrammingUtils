CC = shader 
CFLAGS = -I inc/
EXT = slo
OUT = shaders/superlight.$(EXT)

shaders : $(OUT)

shaders/%.$(EXT) : src/%.sl
	mkdir -p shaders/
	$(CC) $(CFLAGS) -o $@ $<
