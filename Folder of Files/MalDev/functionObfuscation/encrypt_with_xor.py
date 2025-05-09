
import sys

ENCRYPTION_KEY = "123456789ABC"

def xor(input_data, encryption_key):
	
	encryption_key = str(encryption_key)
	l = len(encryption_key)
	output_string = ""

	for i in range(len(input_data)):
		current_data_element = input_data[i]
		current_key = encryption_key[i % len(encryption_key)]
		output_string += chr(ord(current_data_element) ^ ord(current_key))
	
	return output_string

def printCiphertext(ciphertext):
	print('{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')



try:
    plaintext = open(sys.argv[1], "rb").read()
except:
    print("Output file")
    sys.exit()


ciphertext = xor(plaintext, ENCRYPTION_KEY)
print('{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')
