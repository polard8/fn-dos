
# Create APP00.COM.

all: asm-stuff cp-stuff clean
	@echo "APP00.COM OK ?"
asm-stuff:
	nasm main.asm -o APP00.COM
cp-stuff:
	-cp APP00.COM bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm APP00.COM
clean2:
	-rm APP00.COM



