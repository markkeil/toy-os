# ToyOS

# 16-bit
Assemble flat binary 
`nasm -f bin ./boot/boot-16.asm -o ./boot/boot-16.bin`

Test in QEMU
`qemu-system-x86_64 -drive format=raw,file=./boot/boot-16.bin`

# 32-bit
Assemble flat binary 
`nasm -f bin ./boot/boot-32.asm -o ./boot/boot-32.bin`

Test in QEMU
`qemu-system-x86_64 -drive format=raw,file=./boot/boot-32.bin`