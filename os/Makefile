BUILD_DIR=../build/os

AS=nasm
ASFLAGS=-f bin
OS_SRCS!=ls *.asm
OS_OBJS=$(OS_SRCS:.asm=.o)
.SUFFIXES: .o .asm

all: $(OS_OBJS)

.asm.o:
	$(AS) $(ASFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm $(BUILD_DIR)/*
