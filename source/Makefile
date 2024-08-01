
# Create BM2.BIN.
# No shell.
# This is faster version of the boot manager.
# It initializes the pre-selected graphics mode
# and jumps into the BL.BIN.

all: asm-stuff cp-stuff clean
	@echo "KERNEL.BIN OK ?"
asm-stuff:
	nasm kernel.asm -o KERNEL.BIN
cp-stuff:
	-cp KERNEL.BIN ../bin/
clean:
#	find . -type f -name '*.o' -delete
#	-rm KENREL.BIN
clean2:
#	-rm KERNEL.BIN
	
