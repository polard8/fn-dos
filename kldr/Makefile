
# Create BM2.BIN.
# No shell.
# This is faster version of the boot manager.
# It initializes the pre-selected graphics mode
# and jumps into the BL.BIN.

all: asm-stuff cp-stuff clean
	@echo "KLDR.BIN OK ?"
asm-stuff:
	nasm main.asm -o KLDR.BIN
cp-stuff:
	-cp KLDR.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm KLDR.BIN
clean2:
	-rm KLDR.BIN
	
