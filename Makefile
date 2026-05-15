.PHONY: all cleansub

all:
	$(MAKE) -f make_eu.mk
	$(MAKE) -f make_us.mk
	D:\RetroArch\retroarch.exe -L "D:\RetroArch\cores\mednafen_psx_libretro.dll" "D:\psyq\tgw\eu\the_great_warriors_eu.cue"

cleansub:
	rm -f *.o *.dep
	$(MAKE) -f make_eu.mk cleansub
	$(MAKE) -f make_us.mk cleansub