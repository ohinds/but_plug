# from http://audiores.uint8.com.ar/blog/2013/07/29/vst-cross-compiling-in-linux/?utm_source=feedburner&utm_medium=feed&utm_campaign=Feed%3A+AudioResearch+%28Audio+Research+Blog%29

# change this to the location of your unpacked VST SDK:
VSTSDKDIR = $(HOME)/sw/vstsdk

# Change the plugin name here (same name than .h file)
PLUGIN_NAME = delay_compensation

CPP       = i586-mingw32msvc-g++

VST_OBJ = $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o

OBJ       = $(PLUGIN_NAME).o $(VST_OBJ)

LIBS      = -L. --add-stdcall-alias -lole32 -lkernel32 -lgdi32 -luuid -luser32 -mwindows --no-export-all-symbols --def $(PLUGIN_NAME).def

CXXINCS   = -I"$(VSTSDKDIR)/pluginterfaces/vst2.x" -I"$(VSTSDKDIR)/public.sdk/source/vst2.x" -I"$(VSTSDKDIR)" -I"$(VSTSDKDIR)/vstgui.sf/vstgui" -I.
BIN       = $(PLUGIN_NAME).dll
CXXFLAGS  = $(CXXINCS) -DBUILDING_DLL=1 -mwindows -O3 -DDEVELOPMENT
RM        = rm -f

.PHONY: all clean

all: $(PLUGIN_NAME).dll

clean:
	${RM} $(OBJ) $(BIN)

# not we're using mingw dllwrap tool
DLLWRAP   = i586-mingw32msvc-dllwrap

DEFFILE   = lib$(PLUGIN_NAME).def

STATICLIB = lib$(PLUGIN_NAME).a

$(BIN): $(OBJ)
	$(DLLWRAP) --output-def $(DEFFILE) --driver-name $(CPP) --implib $(STATICLIB) $(OBJ) $(LIBS) -o $(BIN)

%.o: %.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o $(CXXFLAGS)
