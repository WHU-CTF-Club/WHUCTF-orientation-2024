from Crypto.Util.number import long_to_bytes, inverse
from sympy import sqrt_mod

p = 287437772536795668161124408204279543493
X = [
    30075186277005939490278391549792881011,
    184006543478040940511714219519949018437,
    110393758160248301685331187162712930847,
    121719927399910254547081385203936395128,
    15959896411971379742243332335274241273,
]
T = [x1 - x0 for x0, x1 in zip(X[:-1], X[1:])]
A = T[1] * pow(T[0], -1, p) % p
B = (X[1] - A * X[0]) % p

a = sqrt_mod(A, p)
b = (B * inverse(a + 1, p)) % p
print(long_to_bytes(a) + long_to_bytes(b))
