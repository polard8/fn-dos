
# Create CMD00.BIN.

all: asm-stuff cp-stuff clean
	@echo "CMD03.BIN OK ?"
asm-stuff:
	nasm main.asm -o CMD03.BIN
cp-stuff:
	-cp CMD03.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm CMD03.BIN
clean2:
	-rm CMD03.BIN


