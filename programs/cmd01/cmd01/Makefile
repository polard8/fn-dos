
# Create CMD01.BIN.

all: asm-stuff cp-stuff clean
	@echo "CMD01.BIN OK ?"
asm-stuff:
	nasm main.asm -o CMD01.BIN
cp-stuff:
	-cp CMD01.BIN bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm CMD01.BIN
clean2:
	-rm CMD01.BIN

