#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>

int padding = RSA_PKCS1_PADDING;

RSA* ingestPublicKey(FILE *fp)
{
 
    if(fp == NULL)
    {
        printf("Unable to open public key file \n");
        return NULL;    
    }
    RSA* rsa= RSA_new() ;
 
    rsa = PEM_read_RSA_PUBKEY(fp, &rsa,NULL, NULL);
    
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
    char *file_contents;
    file_contents = (char*)calloc(1,lSize+1);
    fread(file_contents,lSize,1,filename);

    unsigned char  encrypted[10000]={};

    FILE* public = fopen(argv[2],"rb");
    RSA* rsa = ingestPublicKey(public);  

    int encrypted_length = RSA_public_encrypt((int)strlen(file_contents),file_contents,encrypted,rsa,padding);

    if(encrypted_length == -1)
    {
        printf("Public Encryption failed");
        exit(0);
    }
    printf("Encrypted length is %d\n",encrypted_length);

    FILE* out_filename = fopen(argv[3],"wb");
    fwrite(encrypted, encrypted_length, 1, out_filename);
    // fprintf(out_filename,"%s", encrypted);
    fclose(out_filename);
    fclose(public);
    fclose(filename);
    free(file_contents);
    return 0; 
}