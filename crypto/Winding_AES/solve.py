from Crypto.Cipher import AES
from tqdm import tqdm


def xor(a: bytes, b: bytes):
    assert len(a) == len(b)
    return bytes([x ^ y for x, y in zip(a, b)])


def AES_decrypt(flag: bytes, key: bytes):
    cipher = AES.new(key, AES.MODE_ECB)
    return cipher.decrypt(flag)


C = b"\x84U\xf6\xb7\x86\xd3Zx\xc0\xfc\xf9\xe8A\xb1\xfel"
hint = [
    b"\xf0)\xc2\x1b\xe7\xd0\xb2\xde\x95\xd5\x92\xf8\xa8E\xd8",
    b"\xa7\x87c\xe5D\xa2\x95\x05\x10\x97\xaf\xe8B\x1fy",
    b"\x8c\xcaC\x7f\xcd>>\x1a\x83<~\xed\xd2\x89\r",
    b"\t\xcda\xd9\xa0\xb7\xea\x1a\x9e\x07)\xd4`\xe9\xcf",
    b"\xf8\x7f5\x86\xc8\xc4n`\xad\xa8\x19\xc5\xbe\xfa\xfd",
    b"\x88z\x86\xd1\x1f\xa3k\x1a\xa1*nuy\xf3\x08",
    b"\x90\x8f\xdd\t@\xbb\xc25\xba\x82\xd6\xf1F*+",
    b"\xdbo\xe9^\xfc\xc0\xdb\xce\xc7\xae\xb7\x16\x11\xfbv",
    b"\x03\xaf\x81\x90\x0e0\x90\xactc\x92\x91\x92Y\xcf",
    b"\x9a\xd1\xea\xc4,xO!\x03\xc7^\xf2z\xaf:",
    b"\x1bY\x91\x96\xa9\xf2\xf7m\xe4\xcc\x7f2uB`",
    b"\xc9=Fku7\x9du\tT\xc1p\xd0\xbf\x86",
    b"K\x07\xab\xb1\x88\x81\x88\x17A\xf7\xa8\x0c\x92\xe2a",
    b"\xfb\xba\xa9\xe3\xd6\xba\xfcF\r\xd6\xd3\x1d\xe4\x91\x9b",
    b"\xb5E\xc1UG\x0c\x19\x80\xc8G\xd0\xe2\x9a`\x8f",
    b"V\xb8C\x17}\xd3\xe9;Z$\x82#\xcb\x1c\x95",
]

# recover the full C and key1
for _ in tqdm(range(len(hint) - 1, 0, -1)):
    for h_ in range(256):
        h1 = bytes([h_]) + hint[_]
        h0 = b"\x00" + hint[_ - 1]
        brk = False
        for i in range(256):
            c0 = bytes([i]) + C[:15]
            c1 = C[:16]
            key = xor(h1, c0)
            key = AES_decrypt(xor(key, c1), c0)
            if xor(h0, b"\x00" + c0[:-1])[1:] == key[1:]:
                C = bytes([i]) + C
                brk = True
                if _ == 1:
                    key1 = key
                break
        if brk:
            break

# print(key1)
# key0=b"y\x97\x96\xae\x1cc\x7f\xff\xdcyU%\x9a8{\xf1"

for c_ in range(256):
    fstbyte = bytes([c_])
    c0 = fstbyte + C[:15]
    c1 = C[:16]
    key0 = AES_decrypt(xor(key1, c1), c0)
    flag = AES_decrypt(fstbyte + C, key0)
    if b"WHUCTF" in flag:
        print(flag)
        break
