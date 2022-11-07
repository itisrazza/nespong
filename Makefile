AS = ca65
LD = ld65

project_name = nespong
objects = main.o header.o graphics.o
includes = 

$(project_name).nes: $(objects)
	$(LD) -o $@ -C linker.cfg $^ -m $(project_name).map -Ln $(project_name).labels.txt --dbgfile $@.dbg

%.o: %.s65 $(includes) linker.cfg
	$(AS) -o $@ $<

.PHONY: clean
clean:
	rm $(project_name).nes
	rm *.o
