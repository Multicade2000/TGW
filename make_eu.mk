.PHONY: all cleansub

TARGET = eu/TGW
TYPE = ps-exe

SRCS = main.c \
game.c \
graph.c \
cdrom.c \
sound.c \
controller.c \
memcard.c \
movie.c \
intro.c \
battle.c \
region_eu.c \
../third_party/common/syscalls/printf.s \
../third_party/common/crt0/crt0.s \

CPPFLAGS += -I../third_party/common
CPPFLAGS += -I../third_party/psyq/include
LDFLAGS += -L../third_party/psyq/lib
LDFLAGS += -Wl,--start-group
LDFLAGS += -lapi
LDFLAGS += -lc
LDFLAGS += -lc2
LDFLAGS += -lcd
LDFLAGS += -lcard
LDFLAGS += -lcomb
LDFLAGS += -lds
LDFLAGS += -letc
LDFLAGS += -lgpu
LDFLAGS += -lgs
LDFLAGS += -lgte
LDFLAGS += -lgpu
LDFLAGS += -lgun
LDFLAGS += -lhmd
LDFLAGS += -lmath
LDFLAGS += -lmcrd
LDFLAGS += -lmcx
LDFLAGS += -lpad
LDFLAGS += -lpress
LDFLAGS += -lsio
LDFLAGS += -lsnd
LDFLAGS += -lspu
LDFLAGS += -ltap
LDFLAGS += -Wl,--end-group

include ../third_party/common.mk

all:
	mkpsxiso -y eu/iso.xml

cleansub:
	rm -r eu/TGW.* eu/the_great_warriors_eu.*