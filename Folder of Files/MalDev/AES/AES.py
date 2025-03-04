
import sys
from Crypto.Cipher import AES
from os import urandom
import hashlib

ENCRYPTION_KEY = urandom(16)

def pad(s):
	return s + (AES.block_size - len(s) % AES.block_size) * chr(AES.block_size - len(s) % AES.block_size)

def AES_encrypt(plaintext, key):

	k = hashlib.sha256(key).digest()
	iv = 16 * '\x00'
	plaintext = pad(plaintext)
	cipher = AES.new(k, AES.MODE_CBC, iv)

	return cipher.encrypt(bytes(plaintext))
    
try:
    plaintext = open(sys.argv[1], "r").read()
except:
    print("Incorrect Syntax. Try PAYLOAD > OUTPUT")
    sys.exit()

ciphertext = AES_encrypt(plaintext, ENCRYPTION_KEY)
print('AESkey[] = { 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ENCRYPTION_KEY) + ' };')
print('payload[] = { 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')