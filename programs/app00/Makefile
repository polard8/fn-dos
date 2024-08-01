
# Create APP00.BIN.
# It initializes the bm-shell in 32bit assembly.
# In this shell we can select the graphics mode
# switching back to realmode.
# This was the legacy version of this program.
#

all: asm-stuff cp-stuff clean
	@echo "APP00.BIN OK ?"
asm-stuff:
	nasm app00.asm -o APP00.BIN
cp-stuff:
	-cp APP00.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm APP00.BIN
clean2:
	-rm APP00.BIN
	
