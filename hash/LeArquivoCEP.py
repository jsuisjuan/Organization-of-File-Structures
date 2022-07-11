import struct
import codecs
import sys

fileName = "data/cep.dat"
cepFormat = "72s72s72s72s2s8s2s"
encoding = "latin1"

recordSize = struct.calcsize(cepFormat)

if len(sys.argv) >= 2:
    cepProcurado = sys.argv[1]
else:
    cepProcurado = raw_input("Entre com o cep: ")

f = open(fileName,"rb")
while True:
    line = f.read(recordSize)
    if line == "": # EOF
        break
    record = struct.unpack(cepFormat, line)
    if record[5] == cepProcurado:
        print(codecs.decode(record[0],encoding))
        print(codecs.decode(record[1],encoding))
        print(codecs.decode(record[2],encoding))
        print(codecs.decode(record[4],encoding))
f.close()
