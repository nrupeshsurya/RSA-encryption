all: encrypt decrypt input.txt private.pem public.pem 
	./encrypt input.txt public.pem encrypt.bin
	./decrypt encrypt.bin private.pem decrypt.txt

encrypt: encrypt.c 
	gcc encrypt.c -o encrypt -lcrypto -lssl

decrypt: decrypt.c 
	gcc decrypt.c -o decrypt -lcrypto -lssl

clean:
	rm -rf encrypt decrypt decrypt.txt encrypt.bin