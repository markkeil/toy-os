# ToyOS

Assemble flat binary 
`nasm -f bin ./boot/boot.asm -o ./boot/boot.bin`

Test in QEMU
`qemu-system-x86_64 -drive format=raw,file=./boot/boot.bin`