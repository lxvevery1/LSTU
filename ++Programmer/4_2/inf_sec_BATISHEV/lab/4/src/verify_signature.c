#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <stdio.h>

#define SIGNATURE_SIZE 256

void print_hex(const char* label, unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

void print_openssl_errors() {
    unsigned long err;
    while ((err = ERR_get_error())) {
        fprintf(stderr, "[OPENSSL ERROR] %s\n", ERR_error_string(err, NULL));
    }
}

void verify_signature(const char* file_path, const char* pub_key_path,
                      const char* signature_path) {
    printf("[INFO] Открытие файла для проверки подписи: %s\n", file_path);
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "[ERROR] Ошибка открытия файла\n");
        return;
    }

    printf("[INFO] Вычисление SHA-256 хэша файла...\n");
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

    print_hex("[DEBUG] SHA-256 хэш файла", hash, SHA256_DIGEST_LENGTH);

    printf("[INFO] Загрузка открытого ключа: %s\n", pub_key_path);
    FILE* pub_file = fopen(pub_key_path, "rb");
    if (!pub_file) {
        fprintf(stderr, "[ERROR] Ошибка открытия открытого ключа\n");
        return;
    }

    RSA* rsa = PEM_read_RSA_PUBKEY(pub_file, NULL, NULL, NULL);
    fclose(pub_file);
    if (!rsa) {
        fprintf(stderr, "[ERROR] Ошибка загрузки открытого ключа\n");
        print_openssl_errors();
        return;
    }

    printf("[INFO] Загрузка подписи из файла: %s\n", signature_path);
    FILE* sig_file = fopen(signature_path, "rb");
    if (!sig_file) {
        fprintf(stderr, "[ERROR] Ошибка открытия файла подписи\n");
        RSA_free(rsa);
        return;
    }

    unsigned char signature[SIGNATURE_SIZE];
    size_t sig_size = fread(signature, 1, SIGNATURE_SIZE, sig_file);
    fclose(sig_file);

    if (sig_size != SIGNATURE_SIZE) {
        fprintf(
            stderr,
            "[ERROR] Длина подписи неверная! Ожидаемая: %d, полученная: %zu\n",
            SIGNATURE_SIZE, sig_size);
        RSA_free(rsa);
        return;
    }

    print_hex("[DEBUG] Загруженная подпись", signature, SIGNATURE_SIZE);

    printf("[INFO] Проверка подписи...\n");
    int verify_result = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH,
                                   signature, SIGNATURE_SIZE, rsa);

    if (verify_result) {
        printf("[SUCCESS] Подпись подтверждена!\n");
    } else {
        fprintf(stderr, "[ERROR] Подпись неверна!\n");
        print_openssl_errors();
    }

    RSA_free(rsa);
}

int main() {
    verify_signature("test.txt", "public.pem", "signature_old.bin");
    return 0;
}
