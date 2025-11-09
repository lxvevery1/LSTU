#include <stdio.h>

// Function to calculate the GCD (Euclidean algorithm)
// same as НОД
int gcd(int a, int b) {
    printf("gdc: %d and %d\n", a, b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
        printf("gdc iter: %d and %d\n", a, b);
    }
    printf("gdc returning: %d\n\n", a);
    return a;
}

// Function to calculate (base^exp) % mod (fast exponentiation)
long long mod_exp(long long base, long long exp, long long mod) {
    printf("mod_exp: base=%lld, exp=%lld, mod=%lld", base, exp, mod);
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
            printf("mod_exp: %lld = (%lld * %lld) %% %lld\n", result, result,
                   base, mod);
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function for calculating the inverse element modulo (Extended
// Euclidean algorithm)
int mod_inverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;

    while (new_r != 0) {
        int quotient = r / new_r;
        int temp = new_t;
        new_t = t - quotient * new_t;
        t = temp;
        temp = new_r;
        new_r = r - quotient * new_r;
        r = temp;
    }

    if (r > 1)
        return -1; // Inverse element does not exist
    if (t < 0)
        t += phi;
    return t;
}

int main() {
    // 1. Choose two prime numbers p and q
    int p = 311, q = 419;

    // 2. Calculate n = p * q
    int n = p * q;

    // 3. Calculate the Euler function: φ(n) = (p-1) * (q-1)
    int phi = (p - 1) * (q - 1);

    // 4. Choose e (public key) such that 1 < e < φ(n) and GCD(e, φ(n)) = 1
    int e = 7;
    if (gcd(e, phi) != 1) {
        printf("Error: e and φ(n) must be relatively prime!\n");
        return 1;
    }

    // 5. Calculate d (secret key) satisfying e * d ≡ 1 (mod φ(n))
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Error: Could not find secret key!\n");
        return 1;
    }

    // Print keys
    printf("Public key: (n = %d, e = %d)\n", n, e);
    printf("Private key: (d = %d)\n", d);

    // 6. Encrypt message M = 312
    int message[] = {3, 1, 2};
    int encrypted[3];

    printf("\nEncryption:\n");
    for (int i = 0; i < 3; i++) {
        encrypted[i] = mod_exp(message[i], e, n);
        printf("C%d = %d\n", i + 1, encrypted[i]);
    }

    // 7. Decryption
    int decrypted[3];

    printf("\nDecryption:\n");
    for (int i = 0; i < 3; i++) {
        decrypted[i] = mod_exp(encrypted[i], d, n);
        printf("M%d = %d\n", i + 1, decrypted[i]);
    }

    printf("\nOriginal message: %d%d%d\n", decrypted[0], decrypted[1],
           decrypted[2]);

    return 0;
}
