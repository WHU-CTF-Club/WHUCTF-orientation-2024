import os
from itertools import product
from random import choices
from string import ascii_lowercase

path = "./steam"
if not os.path.exists(path):
    os.mkdir(path)
part1 = ["steam", "stem", "stam", "蒸汽平台", "staem", "stream"]
part2 = ["手机版", "启动器", "破解版", "电脑版", "正版", "社区", "会员版", ""]


def gen(path):
    for p1, p2 in product(part1, part2):
        p0 = "".join(choices(ascii_lowercase, k=4))
        name = p0 + "_" + p1 + p2
        os.mkdir(os.path.join(path, name))


def scan_and_gen(path):
    dirs = os.listdir(path)
    for d in dirs:
        if os.path.isdir(os.path.join(path, d)):
            gen(os.path.join(path, d))


def scan_and_scan(path):
    dirs = os.listdir(path)
    for d in dirs:
        p = os.path.join(path, d)
        scan_and_gen(p)


gen(path)
scan_and_gen(path)
# scan_and_scan(path)
