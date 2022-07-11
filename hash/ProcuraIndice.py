import struct
import hashlib
import os
import sys

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

fi = open(indexName,"rb")
f = open(fileName,"rb")

if len(sys.argv) >= 2:
    cepProcurado = sys.argv[1]
else:
    cepProcurado = raw_input("Entre com o cep: ")

p = h(cepProcurado)
offset = p*indexStruct.size
i = 1
while True:
    fi.seek(offset,os.SEEK_SET)
    indexRecord = indexStruct.unpack(fi.read(indexStruct.size))
    if indexRecord[0] == cepProcurado:
        f.seek(indexRecord[1]*dataStruct.size,os.SEEK_SET)
        record = dataStruct.unpack(f.read(dataStruct.size))
        print(record)
        print(i)
        break
    offset = indexRecord[2]
    if offset == 0:
        break
    i += 1
fi.close()
