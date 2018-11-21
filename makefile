# Source file stuff
GAME := game.exe
GAME_SRC := $(wildcard src/*.cpp)
GAME_HED := $(wildcard src/*.h)
GAME_OBJ := $(patsubst src/%.cpp,%.obj,$(GAME_SRC))

# Compiler stuff
CC := cl
LDFLAGS := -link -subsystem:console -machine:x86 -libpath:C:/devlibs/SDL2/lib/x86 \
           -libpath:C:/devlibs/SDL2_image/lib/x86 -debug:full -out:$(GAME) -nologo
CFLAGS := -c -EHsc -nologo
LLIBS := SDL2main.lib SDL2.lib SDL2_image.lib

# Compiling and linking
%.obj: src/%.cpp src/*.h
	$(CC) $(CFLAGS) $<

all: $(GAME)

$(GAME): $(GAME_OBJ)
	$(CC) $(GAME_OBJ) $(LLIBS) $(LDFLAGS)

# Cleaning
.PHONY: clean

clean:
	rm -f *.obj *.exe *.exp *.lib *.ilk *.pdb