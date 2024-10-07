import hashlib
import re

secret = "????????????????"
assert re.match(r"^[_a-z0-9]*+$", secret)
assert re.match(r"^guess_([mnpq][x-z])_r(.)g\2x_\d{4}_collide_\1_h[^e-z0-9]sh$", secret)
flag = "WHUCTF{" + secret + "}"
secret_hash = hashlib.md5(secret.encode()).hexdigest()
print(secret_hash)

# 41c265a60258cff5b087d52eb5f64bde
