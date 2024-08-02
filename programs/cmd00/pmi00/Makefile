
# Create BM.BIN.
# It initializes the bm-shell in 32bit assembly.
# In this shell we can select the graphics mode
# switching back to realmode.
# This was the legacy version of this program.
#

all: asm-stuff cp-stuff clean
	@echo "PMI00.BIN OK ?"
asm-stuff:
	nasm main.asm -o PMI00.BIN
cp-stuff:
	-cp PMI00.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm PMI00.BIN
clean2:
	-rm PMI00.BIN
	
