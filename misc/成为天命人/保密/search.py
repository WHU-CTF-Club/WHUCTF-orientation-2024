import os

path = "./steam"


def DFS(path):
    dirs = os.listdir(path)
    for d in dirs:
        if os.path.isdir(os.path.join(path, d)):
            DFS(os.path.join(path, d))
        else:
            print(os.path.join(path, d))


DFS(path)
