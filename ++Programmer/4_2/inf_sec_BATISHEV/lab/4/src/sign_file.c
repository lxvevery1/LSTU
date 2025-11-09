#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <stdio.h>

#define SIGNATURE_SIZE 256

void sign_file(const char* file_path, const char* priv_key_path,
               const char* signature_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла\n");
        return;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    unsigned char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        SHA256_Update(&sha256, buffer, bytes_read);
    }
    fclose(file);
    SHA256_Final(hash, &sha256);

    FILE* priv_file = fopen(priv_key_path, "rb");
    if (!priv_file) {
        fprintf(stderr, "Ошибка открытия закрытого ключа\n");
        return;
    }

    RSA* rsa = PEM_read_RSAPrivateKey(priv_file, NULL, NULL, NULL);
    fclose(priv_file);
    if (!rsa) {
        fprintf(stderr, "Ошибка загрузки закрытого ключа\n");
        return;
    }

    unsigned char signature[SIGNATURE_SIZE];
    unsigned int sig_len;
    if (!RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &sig_len,
                  rsa)) {
        fprintf(stderr, "Ошибка подписания\n");
        RSA_free(rsa);
        return;
    }
    RSA_free(rsa);

    FILE* sig_file = fopen(signature_path, "wb");
    fwrite(signature, 1, sig_len, sig_file);
    fclose(sig_file);

    printf("Файл подписан!\n");
}

int main() {
    sign_file("test.txt", "private.pem", "signature.bin");
    return 0;
}
