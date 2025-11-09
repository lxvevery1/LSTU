#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <stdio.h>

#define KEY_SIZE 2048

void generate_keys(const char* priv_key_file, const char* pub_key_file) {
    RSA* rsa = RSA_generate_key(KEY_SIZE, RSA_F4, NULL, NULL);
    if (!rsa) {
        fprintf(stderr, "Ошибка генерации ключей\n");
        return;
    }

    FILE* priv_file = fopen(priv_key_file, "wb");
    if (!priv_file) {
        fprintf(stderr, "Ошибка создания файла закрытого ключа\n");
        RSA_generate_key;
        return;
    }
    PEM_write_RSAPrivateKey(priv_file, rsa, NULL, NULL, 0, NULL, NULL);
    fclose(priv_file);

    FILE* pub_file = fopen(pub_key_file, "wb");
    if (!pub_file) {
        fprintf(stderr, "Ошибка создания файла открытого ключа\n");
        RSA_free(rsa);
        return;
    }
    PEM_write_RSA_PUBKEY(pub_file, rsa);
    fclose(pub_file);

    RSA_free(rsa);
    printf("Ключи сгенерированы!\n");
}

int main() {
    generate_keys("private.pem", "public.pem");
    return 0;
}
