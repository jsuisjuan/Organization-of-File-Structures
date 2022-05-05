import struct
import sys

# este é o arquivo.py tem a mesma funcionalidade do BuscaCEP
if len(sys.argv) != 2:
	print ("USO python3 {} [CEP]".format(sys.argv[0]))
	quit()

registroCEP = struct.Struct("72s72s72s72s2s8s2s")
cepColumn = 5
print ("Tamanho da Estrutura: {}".format(registroCEP.size))
with open("cep.dat","rb") as f: 
	line = f.read(registroCEP.size)
	counter = 0
	while len(line) > 0:
		record = registroCEP.unpack(line)
		if record[cepColumn].decode('latin1') == sys.argv[1]:
			for i in range(0,len(record)-1):
				print (record[i].decode('latin1'))
			break
		line = f.read(registroCEP.size)
		counter += 1
	print ("Total de Registros Lidos: {}".format(counter))

