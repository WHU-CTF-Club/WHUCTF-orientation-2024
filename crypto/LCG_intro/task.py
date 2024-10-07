from Crypto.Util.number import *

flag = b"??????????????"
length = len(flag)
a = bytes_to_long(flag[: length // 2])
b = bytes_to_long(flag[length // 2 :])
p = getPrime(128)
assert a < p and b < p


class LCG:
    def __init__(self, a, b, p):
        self.state = a * b % p
        self.a = a
        self.b = b
        self.p = p

    def next(self):
        self.state = (self.a * self.state + self.b) % self.p
        return self.state

    def double_next(self):
        self.state = (self.a * self.state + self.b) % self.p
        self.state = (self.a * self.state + self.b) % self.p
        return self.state


lcg = LCG(a, b, p)
print(p)
print([lcg.double_next() for _ in range(5)])
"""
287437772536795668161124408204279543493
[30075186277005939490278391549792881011, 184006543478040940511714219519949018437, 110393758160248301685331187162712930847, 121719927399910254547081385203936395128, 15959896411971379742243332335274241273]
"""
