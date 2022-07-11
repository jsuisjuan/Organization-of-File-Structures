import struct
import hashlib
import os

hashSize = 900001
fileName = "data/cep.dat"
indexName = "data/cep-hash.dat"
dataFormat = "72s72s72s72s2s8s2s"
indexFormat = "8sLL"
keyColumnIndex = 5

dataStruct = struct.Struct(dataFormat)
indexStruct = struct.Struct(indexFormat)

def h(key):
    return int(hashlib.sha1(key).hexdigest(),16)%hashSize

fi = open(indexName,"wb")
emptyIndexRecord = indexStruct.pack("",0,0)
for i in range(0,hashSize):
    fi.write(emptyIndexRecord)
fi.close()

f = open(fileName,"rb")
fi = open(indexName,"r+b")

fi.seek(0,os.SEEK_END)
fileIndexSize = fi.tell()

recordNumber = 0
while True:
    line = f.read(dataStruct.size)
    if line == "": # EOF
        break
    record = dataStruct.unpack(line)
    key = record[keyColumnIndex] 
    p = h(key)
    fi.seek(p*indexStruct.size,os.SEEK_SET)
    indexRecord = indexStruct.unpack(fi.read(indexStruct.size))
    fi.seek(p*indexStruct.size,os.SEEK_SET)
    if indexRecord[0][0] == "\0":
        fi.write(indexStruct.pack(key,recordNumber,0))
    else:
        nextPointer = indexRecord[2]
        fi.write(indexStruct.pack(indexRecord[0],indexRecord[1],fileIndexSize))
        fi.seek(0,os.SEEK_END)
        fi.write(indexStruct.pack(key,recordNumber,nextPointer))
        fileIndexSize = fi.tell()
    recordNumber += 1
f.close()
fi.close()
