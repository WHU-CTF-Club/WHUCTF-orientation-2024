from itertools import product
from string import ascii_lowercase, digits
import hashlib


def get1():
    for i in product("mnpq", "xyz"):
        yield "".join(i)


def get2():
    for i in ascii_lowercase + digits:
        yield i


def get3():
    for i in product(digits, repeat=4):
        yield "".join(i)


def get4():
    for i in "abcd":
        yield "".join(i)


secret = "guess_{}_r{}g{}x_{}_collide_{}_h{}sh"
target = "41c265a60258cff5b087d52eb5f64bde"
for x1 in get1():
    for x2 in get2():
        for x3 in get3():
            for x4 in get4():
                guess = secret.format(x1, x2, x2, x3, x1, x4)
                if hashlib.md5(guess.encode()).hexdigest() == target:
                    print("WHUCTF{" + guess + "}")
                    exit(0)
