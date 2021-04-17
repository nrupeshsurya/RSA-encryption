#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
 
int padding = RSA_PKCS1_PADDING;

RSA * ingestPrivateKey(FILE *fp)
{
    if(fp == NULL)
    {
        printf("Unable to open private key file \n");
        return NULL;    
    }
    RSA *rsa= RSA_new() ;
 
    rsa = PEM_read_RSAPrivateKey(fp, &rsa,NULL, NULL);
 
    return rsa;
}
 
int main(int argc, char* argv[])
{

    if(argc<4)
    {
        printf("Not enough arguements");
        exit(0);
    }

    FILE* filename = fopen(argv[1],"rb");
    long lSize;
    fseek( filename , 0L , SEEK_END);
    lSize = ftell( filename );
    rewind( filename );
    unsigned char *file_contents;
    file_contents = (unsigned char*)malloc(sizeof(char)*lSize);
    fread(file_contents,lSize,1,filename);

    unsigned char decrypted[10000]={};

    FILE* private = fopen(argv[2],"rb");
    RSA * rsa = ingestPrivateKey(private);   

    int decrypted_length = RSA_private_decrypt((int)lSize,file_contents,decrypted,rsa,padding);

    if(decrypted_length == -1)
    {
        printf("Private Decryption failed. Please run again\n");
        exit(0);
    }
    printf("Decrypted length is %d\n",decrypted_length);

    FILE* out_filename = fopen(argv[3],"wb");
    fprintf(out_filename,"%s", decrypted);
    
    return 0; 
}