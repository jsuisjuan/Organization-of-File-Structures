import struct   #importa a biblioteca struct

registroCEP = struct.Struct("72s72s72s72s2s8s2s")
ufColumn = 4
cepColumn = 5

ufAtual = ""
arquivoSaida = None

with open("cep.dat", "rb") as f:
    line = f.read(registroCEP.size)

    while len(line) > 0:
        record = registroCEP.unpack(line)   #transforma de binário para string
        if record[ufColumn].decode('latin1') == ufAtual:
            arquivoSaida.write(line)
        else:
            if arquivoSaida != None:
                arquivoSaida.close()

            ufAtual = record[ufColumn].decode('latin1')
            arquivoSaida = open(f'./arqCep/CEP-{ufAtual}.dat', 'ab')
            arquivoSaida.write(line)

        line = f.read(registroCEP.size)
