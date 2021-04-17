# Lab 9

Public key-private key encryption and decryption
## Compiling

The files can be compiled traditionally using gcc
```bash
gcc encrypt.c -o encrypt -lcrypto -lssl #for producing ./encrypt which runs the encryption
gcc decrypt.c -o decrypt -lcrypto -lssl #for producing ./decrypt which runs the decryption
```

The included makefile has the commands for generating the encryption and decryption program which is same as the above

```bash
make encrypt #for producing ./encrypt which runs the encryption
make decrypt #for producing ./decrypt which runs the decryption
```

## Usage

```bash
./encrypt input.txt public.pem encrypt.bin 
#public.pem is the public key and encrypt.bin is the output file
./decrypt encrypt.bin private.pem decrypt.txt
#private.pem is the private key and decrypt.txt is the output file
```

## Generation of keys
Private and corresponding keys were generated using OpenSSL command line utility

```bash
openssl genrsa -out private.pem 2048
#length is 2048 which can be modified according to needs
openssl rsa -in private.pem -outform PEM -pubout -out public.pem
#generate corresponding public key
```

## Shortcuts

Command for running a sample test case with input.txt
```bash
make
```
