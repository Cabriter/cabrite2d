CFLAGS = -g -Wall -Ilib -Ilib/render -Ilua -D CABRITE2D_OS=$(OS) -D FONT_EDGE_HASH
LDFLAGS :=

RENDER := \
lib/render/carry.c \
lib/render/log.c

EJOY2D := \

SRC := $(EJOY2D) $(RENDER)

LUASRC := \
lua/lapi.c \
lua/lauxlib.c \
lua/lbaselib.c \
lua/lbitlib.c \
lua/lcode.c \
lua/lcorolib.c \
lua/lctype.c \
lua/ldblib.c \
lua/ldebug.c \
lua/ldo.c \
lua/ldump.c \
lua/lfunc.c \
lua/lgc.c \
lua/linit.c \
lua/liolib.c \
lua/llex.c \
lua/lmathlib.c \
lua/lmem.c \
lua/loadlib.c \
lua/lobject.c \
lua/lopcodes.c \
lua/loslib.c \
lua/lparser.c \
lua/lstate.c \
lua/lstring.c \
lua/lstrlib.c \
lua/ltable.c \
lua/ltablib.c \
lua/ltm.c \
lua/lundump.c \
lua/lutf8lib.c \
lua/lvm.c \
lua/lzio.c

CC=gcc
UNAME=$(shell uname)
SYS=$(if $(filter Linux%,$(UNAME)),linux,\
    	$(if $(filter MINGW%,$(UNAME)),mingw,\
	$(if $(filter Darwin%,$(UNAME)),macosx,\
)))

all: $(SYS)

undefined:
	@echo "I can't guess platform,please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "		linux mingw macosx"

macosx : CC :=clang
macosx : OS :=MACOSX
macosx : TARGET :=cab2d
macosx : CFLAGS += -I/usr/include $(shell freetype-config --cflags) -D __MACOSX
macosx : LDFLAGS += -lglfw -framework OpenGL -lfreetype -lm -ldl
macosx : SRC += mac/example/example/window.c mac/example/example/winfw.c mac/example/example/winfont.c

macosx : $(SRC) cab2d

cab2d :
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LUASRC) $(LDFLAGS)

clean :
	-rm -f cab2d
