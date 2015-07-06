import sys
import os

def termsize():
    return list(map(int, os.popen('stty size','r').read().split()))
    #return [ int(v) for v in os.popen('stty size','r').read().split() ]
def termwidth():
    return termsize()[1]
def termheight():
    return termsize()[0]

def errormesg(*message):
    print()
    print()
    #print( termwidth() * '=' )
    print( termwidth() * '=' )
    print()
    print('  ', *message, file=sys.stderr)
    print()
    print( termwidth() * '=' )
    print()
    print()

def mkdirp(path):
    if os.path.isfile(path):
        raise FileExistsError("'%s' is a file, can't create directory" % path)
    if os.path.isdir(path):
        raise IsADirectoryError("The dirctory '%s' already exists" % path)
    os.makedirs(path)

    
    
