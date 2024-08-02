
# Create CMD00.BIN.

all: asm-stuff cp-stuff clean
	@echo "CMD00.BIN OK ?"
asm-stuff:
	nasm main.asm -o CMD00.BIN
cp-stuff:
	-cp CMD00.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm CMD00.BIN
clean2:
	-rm CMD00.BIN
	
