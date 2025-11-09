#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 2048
#define SIGNATURE_SIZE 256

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
// Приватный ключ – используется для создания подписи.
// Публичный ключ – используется для проверки подписи.
// Создаётся контекст EVP_PKEY_CTX для RSA (EVP_PKEY_CTX_new_id(EVP_PKEY_RSA,
// NULL)). Устанавливается длина ключа (2048 бит)
// EVP_PKEY_CTX_set_rsa_keygen_bits(). Генерируется ключ с помощью
// EVP_PKEY_keygen(). Записываем приватный ключ в private_key.pem с
// PEM_write_PrivateKey(). Записываем публичный ключ в public_key.pem с
// PEM_write_PUBKEY()./
int generate_key_pair(const char* priv_key_file, const char* pub_key_file) {
    printf("[INFO] Generating RSA key pair...\n");
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx)
        handle_errors("Failed to create EVP_PKEY_CTX");

    if (EVP_PKEY_keygen_init(ctx) <= 0)
        handle_errors("Failed to initialize keygen");
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, KEY_LENGTH) <= 0)
        handle_errors("Failed to set key length");

    EVP_PKEY* pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
        handle_errors("Key generation failed");

    // Save private key
    FILE* priv_key_fp = fopen(priv_key_file, "wb");
    if (!priv_key_fp) {
        perror("[ERROR] Unable to open private key file");
        return 0;
    }
    PEM_write_PrivateKey(priv_key_fp, pkey, NULL, NULL, 0, NULL, NULL);
    fclose(priv_key_fp);
    printf("[INFO] Private key saved to %s\n", priv_key_file);

    // Save public key
    FILE* pub_key_fp = fopen(pub_key_file, "wb");
    if (!pub_key_fp) {
        perror("[ERROR] Unable to open public key file");
        return 0;
    }
    PEM_write_PUBKEY(pub_key_fp, pkey);
    fclose(pub_key_fp);
    printf("[INFO] Public key saved to %s\n", pub_key_file);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    return 1;
}

// Загружаем приватный ключ из private_key.pem (PEM_read_PrivateKey()).
// Создаём контекст подписания EVP_MD_CTX_new().
// Запускаем процесс подписания EVP_DigestSignInit().
// Передаём в подпись наш хеш файла (EVP_DigestSignUpdate()).
// Генерируем цифровую подпись EVP_DigestSignFinal() и записываем её в sig.
int sign_file(const char* file_path, const char* priv_key_file,
              unsigned char* sig, size_t* sig_len) {
    printf("[INFO] Signing file: %s\n", file_path);

    FILE* file = fopen(file_path, "rb");
    if (!file) {
        perror("[ERROR] Unable to open file for signing");
        return 0;
    }

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx)
        handle_errors("Failed to create MD context");

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) <= 0)
        handle_errors("Failed to initialize digest");

    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file))) {
        if (EVP_DigestUpdate(mdctx, buffer, bytes_read) <= 0)
            handle_errors("Failed to update digest");
    }
    fclose(file);

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) <= 0)
        handle_errors("Failed to finalize digest");
    EVP_MD_CTX_free(mdctx);
    printf("[INFO] Hash calculated successfully\n");
    print_hex("[DEBUG] File hash (SHA-256)", hash, hash_len);

    FILE* priv_key_fp = fopen(priv_key_file, "rb");
    if (!priv_key_fp) {
        perror("[ERROR] Unable to open private key file");
        return 0;
    }
    EVP_PKEY* pkey = PEM_read_PrivateKey(priv_key_fp, NULL, NULL, NULL);
    fclose(priv_key_fp);
    if (!pkey)
        handle_errors("Failed to read private key");

    EVP_MD_CTX* sig_ctx = EVP_MD_CTX_new();
    if (!sig_ctx)
        handle_errors("Failed to create signature context");

    if (EVP_DigestSignInit(sig_ctx, NULL, EVP_sha256(), NULL, pkey) <= 0)
        handle_errors("Failed to initialize signing");
    if (EVP_DigestSignUpdate(sig_ctx, hash, hash_len) <= 0)
        handle_errors("Failed to update signing");
    if (EVP_DigestSignFinal(sig_ctx, sig, sig_len) <= 0)
        handle_errors("Failed to finalize signing");

    print_hex("[DEBUG] Generated signature", sig, *sig_len);

    EVP_MD_CTX_free(sig_ctx);
    EVP_PKEY_free(pkey);

    printf("[INFO] File signed successfully\n");
    return 1;
}

// Открываем файл и считаем его содержимое.
// Вычисляем SHA-256 хеш (так же, как в sign_file()).
// Загружаем публичный ключ из public_key.pem (PEM_read_PUBKEY()).
// Создаём контекст проверки EVP_MD_CTX_new().
// Запускаем процесс проверки EVP_DigestVerifyInit().
// Передаём вычисленный хеш файла EVP_DigestVerifyUpdate().
// Вызываем EVP_DigestVerifyFinal() для проверки:
int verify_signature(const char* file_path, const char* pub_key_file,
                     unsigned char* sig, size_t sig_len) {
    printf("[INFO] Verifying signature for file: %s\n", file_path);

    FILE* file = fopen(file_path, "rb");
    if (!file) {
        perror("[ERROR] Unable to open file for verification");
        return 0;
    }

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx)
        handle_errors("Failed to create MD context");

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) <= 0)
        handle_errors("Failed to initialize digest");

    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file))) {
        if (EVP_DigestUpdate(mdctx, buffer, bytes_read) <= 0)
            handle_errors("Failed to update digest");
    }
    fclose(file);

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) <= 0)
        handle_errors("Failed to finalize digest");
    EVP_MD_CTX_free(mdctx);

    printf("[INFO] Hash calculated successfully for verification\n");
    print_hex("[DEBUG] Verification hash (SHA-256)", hash, hash_len);

    FILE* pub_key_fp = fopen(pub_key_file, "rb");
    if (!pub_key_fp) {
        perror("[ERROR] Unable to open public key file");
        return 0;
    }
    EVP_PKEY* pkey = PEM_read_PUBKEY(pub_key_fp, NULL, NULL, NULL);
    fclose(pub_key_fp);
    if (!pkey)
        handle_errors("Failed to read public key");

    EVP_MD_CTX* verify_ctx = EVP_MD_CTX_new();
    if (!verify_ctx)
        handle_errors("Failed to create verification context");

    if (EVP_DigestVerifyInit(verify_ctx, NULL, EVP_sha256(), NULL, pkey) <= 0)
        handle_errors("Failed to initialize verification");
    if (EVP_DigestVerifyUpdate(verify_ctx, hash, hash_len) <= 0)
        handle_errors("Failed to update verification");
    int result = EVP_DigestVerifyFinal(verify_ctx, sig, sig_len);

    EVP_MD_CTX_free(verify_ctx);
    EVP_PKEY_free(pkey);

    if (result == 1) {
        printf("[SUCCESS] Signature is valid!\n");
        return 1;
    } else {
        printf("[FAIL] Signature is INVALID!\n");
        return 0;
    }
}

// Генерируется пара ключей (RSA 2048).
// Хешируется содержимое файла с помощью SHA-256.
// Приватный ключ подписывает хеш и создаётся цифровая подпись.
// Публичный ключ проверяет подпись, сравнивая её с хешем файла.
int main() {
    const char* priv_key_file = "private_key.pem";
    const char* pub_key_file = "public_key.pem";
    const char* file_to_sign = "example.txt";
    unsigned char sig[SIGNATURE_SIZE];
    size_t sig_len;
    //
    // if (!generate_key_pair(priv_key_file, pub_key_file)) {
    //     fprintf(stderr, "Key generation failed\n");
    //     return 1;
    // }
    //
    // if (!sign_file(file_to_sign, priv_key_file, sig, &sig_len)) {
    //     fprintf(stderr, "Signing failed\n");
    //     return 1;
    // }

    printf("Signature generated successfully\n");

    if (verify_signature(file_to_sign, pub_key_file, sig, sig_len)) {
        printf("Signature is valid\n");
    } else {
        printf("Signature is invalid\n");
    }

    return 0;
}
