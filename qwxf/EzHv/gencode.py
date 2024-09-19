from keystone import *

ks = Ks(KS_ARCH_X86, KS_MODE_16)

IO_PORT_PUTCHAR = 11451
IO_PORT_READROM = 19198
IO_PORT_GETCHAR = 0x410
IO_PORT_DBG_HEX = 0xdead
IO_PORT_VERIFY = 0xbeef

CPUID_GET_RC4KEY = 0x0123
CPUID_READSTRING = 0x4567
CPUID_FORMATCHECK = 0x89ab
CPUID_RC4EXTRAXOR = 0xcdef

def _puts(str, newline = True):
    result = ""
    for c in str:
        result += _putchar(ord(c))
    if newline:
        result += _putchar(10)
    return result

def _putchar(val):
    return f"""
    push ax
    push dx
    mov al, {val}
    mov dx, {IO_PORT_PUTCHAR}
    out dx, al
    pop dx
    pop ax
"""

def _putdbg(val):
    return f"""
    push ax
    push dx
    mov al, {val}
    mov dx, {IO_PORT_DBG_HEX}
    out dx, al
    pop dx
    pop ax
"""

def _verify(val):
    return f"""
    push ax
    push dx
    mov al, {val}
    mov dx, {IO_PORT_VERIFY}
    out dx, al
    pop dx
    pop ax
"""

def _getchar(index):
    return f"""
    push ax
    push dx
    mov al, {index}
    mov dx, {IO_PORT_GETCHAR}
    out dx, al
    pop dx
    add sp, 2
"""

def _readrom(index):
    return f"""
    push ax
    push dx
    mov al, {index}
    mov dx, {IO_PORT_READROM}
    out dx, al
    pop dx
    add sp, 2
"""

def _verify(val):
    return f"""
    push ax
    push dx
    mov al, {val}
    mov dx, {IO_PORT_VERIFY}
    out dx, al
    pop dx
    add sp, 2
"""

code, count = ks.asm(f"""
    mov ax, 0x200
    mov ds, ax
    mov ax, 0x300
    mov es, ax
    mov ax, 0x400
    mov ss, ax
    mov sp, 0x100
    mov bp, sp
                     
    {_readrom(0)}

    mov cx, ax
    xor bx, bx
print_welcome_message_begin:
    cmp bx, cx
    je print_welcome_message_end

    inc bx    
    {_readrom('bl')}
    {_putchar('al')}

    jmp print_welcome_message_begin
print_welcome_message_end:

    mov ax, {CPUID_GET_RC4KEY}
    cpuid

    xchg al, ah
    mov ds:[0x00], ax
    xchg bl, bh
    mov ds:[0x02], bx
    xchg cl, ch
    mov ds:[0x04], cx
    xchg dl, dh
    mov ds:[0x06], dx

    mov ax, {CPUID_READSTRING}
    mov bx, 32
    cpuid

    cmp ax, bx
    jne wrong

    mov ax, {CPUID_FORMATCHECK}
    cpuid
    test al, al
    je wrong

    mov cx, 32
    xor bx, bx
get_input_begin:
    cmp bx, cx
    je get_input_end
    {_getchar('bl')}
    mov es:[bl], al
    inc bx
    jmp get_input_begin
get_input_end:

    mov si, 0x100 # sbox: ds:[0x100]
    mov di, 0x0   # rc4key: ds:[0x0]
    call _rc4_init

    mov si, 0x100
    mov di, 0
    call _rc4_crypt

    mov si, 0x100
    call _rc4_load_sbox

    mov si, 0x100
    mov di, 1
    call _rc4_crypt

    # do verify
    xor bx, bx
final_verify_begin:
    cmp bx, 32
    je final_verify_end
    mov al, es:[bx]
    {_verify('al')}
    test al, al
    jz wrong
    inc bx
    jmp final_verify_begin
final_verify_end:

correct:
    {_puts("Correct!")}
    hlt
    
wrong:
    {_puts("Wrong!")}
    hlt

# si: sbox
# di: rc4 key
_rc4_init:
    push bp
    sub sp, 0x100   # k buffer

    xor ax, ax # i = 0
rc4_init_loop_1_begin:
    cmp ax, 0x100
    je rc4_init_loop_1_end
    mov bx, si
    add bx, ax
    mov ds:[bx], al # s[i] = i
    mov bx, ax
    and bx, 7
    add bx, di
    mov cl, ds:[bx] # cl = key[i % Len]
    mov bx, sp
    add bx, ax
    mov ss:[bx], cl # k[i] = key[i % Len]
    inc ax
    jmp rc4_init_loop_1_begin
rc4_init_loop_1_end:

    xor ax, ax # i = 0
    xor ch, ch # j = 0
    xor cl, cl # tmp = 0
rc4_init_loop_2_begin:
    cmp ax, 0x100
    je rc4_init_loop_2_end
    
    mov bx, si
    add bx, ax
    add ch, ds:[bx] # j += s[i]
    mov bx, sp
    add bx, ax
    add ch, ss:[bx] # j += k[i]
    # swap s[i] and s[j]
    mov bx, si
    movzx dx, ch
    add bx, dx
    mov dh, ds:[bx]
    mov di, bx
    mov bx, si
    add bx, ax
    mov dl, ds:[bx]
    mov ds:[bx], dh
    mov bx, di
    mov ds:[bx], dl

    inc ax
    jmp rc4_init_loop_2_begin
rc4_init_loop_2_end:
    add sp, 0x100
    pop bp
    ret

# si: sbox
_rc4_load_sbox:
    xor bl, bl
rc4_load_sbox_loop_begin:
    cmp bl, 128
    je rc4_load_sbox_loop_end
    mov al, 128
    add al, bl
    {_readrom('al')}
    mov ds:[si], al
    inc si
    mov ds:[si], ah
    inc si
    inc bl
    jmp rc4_load_sbox_loop_begin
rc4_load_sbox_loop_end:
    ret

# si: buffer
# di: xor key index
_rc4_crypt:
    push bp
    xor bp, bp # k = 0
    xor ax, ax # al: i, ah: j
rc4_crypt_begin:
    cmp bp, 32
    je rc4_crypt_end

    inc al
    movzx bx, al
    add bx, si
    mov cl, ds:[bx]
    add ah, cl

    movzx bx, al
    add bx, si
    mov dl, ds:[bx]
    movzx bx, ah
    add bx, si
    mov dh, ds:[bx]
    mov ds:[bx], dl
    movzx bx, al
    add bx, si
    mov ds:[bx], dh

    add dl, dh
    movzx bx, dl
    add bx, si
    mov dl, ds:[bx]
    mov bx, di
    mov dh, bl
    push ax
    mov ax, {CPUID_RC4EXTRAXOR}
    cpuid
    pop ax
    
    mov bl, es:[bp]
    xor bl, dl
    mov es:[bp], bl
    inc bp
    jmp rc4_crypt_begin
rc4_crypt_end:
    pop bp
    ret

# si: buffer
# di: length
_dbg_print_memory:
    xor bx, bx
dbg_loop_begin:
    cmp bx, di
    je dbg_loop_end
    mov cx, si
    add cx, bx
    mov cl, ds:[cx]
    {_putchar('cl')}
    inc bx
    jmp dbg_loop_begin
dbg_loop_end:
    {_putchar(10)}
    ret

# si: buffer
# di: length
_dbg_print_memory_hex:
    xor bx, bx
dbg_loop_hex_begin:
    cmp bx, di
    je dbg_loop_hex_end
    mov cx, si
    add cx, bx
    mov cl, ds:[cx]
    {_putdbg('cl')}
    inc bx
    jmp dbg_loop_hex_begin
dbg_loop_hex_end:
    {_putchar(10)}
    ret

_dump_sbox:
    push si
    push di
    mov si, 0x100
    mov di, 256
    call _dbg_print_memory_hex
    {_putchar(10)}
    pop di
    pop si
    ret
    
""", 0x1000, True)


RESULT_PREFIX = """#pragma once

// This file is generated by script! You shouldn't manually edit it!
// <! This file should only be included in EzHv.cpp !>

constexpr unsigned char code[] = 
{ 
"""

result = ""
for i in range(0, len(code), 16):
    result += '    '
    for j in range(16):
        if i + j < len(code):
            result += '0x%02x, ' % code[i + j]
        else:
            break
    result += '\n'

result = RESULT_PREFIX + result + '};'
print(result)

with open('hv_code.h', 'w') as f:
    f.write(result + '\n')
