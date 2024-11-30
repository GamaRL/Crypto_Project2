#include <stdio.h>
#include <string.h>
#include <oqs/oqs.h>

// Test a given signature algorithm with a specific key and message
void test_signature_algorithm(const char *algorithm, const uint8_t *message, size_t message_len) {
    if (!OQS_SIG_alg_is_enabled(algorithm)) {
        printf("El algoritmo %s no está habilitado en esta instalación de liboqs.\n", algorithm);
        return;
    }

    OQS_SIG *sig = OQS_SIG_new(algorithm);
    if (sig == NULL) {
        printf("Error al inicializar el algoritmo %s.\n", algorithm);
        return;
    }

    uint8_t public_key[sig->length_public_key];
    uint8_t secret_key[sig->length_secret_key];
    uint8_t signature[sig->length_signature];
    size_t signature_len;

    // Generate keypair
    OQS_SIG_keypair(sig, public_key, secret_key);

    // Sign the message
    OQS_STATUS sign_status = OQS_SIG_sign(sig, signature, &signature_len, message, message_len, secret_key);
    if (sign_status != OQS_SUCCESS) {
        printf("Error al firmar el mensaje con %s.\n", algorithm);
        OQS_SIG_free(sig);
        return;
    }

    // Verify the signature
    OQS_STATUS verify_status = OQS_SIG_verify(sig, message, message_len, signature, signature_len, public_key);

    printf("Resultados para el algoritmo %s:\n", algorithm);
    printf("  ¿Firma válida?: %s\n", (verify_status == OQS_SUCCESS) ? "Sí" : "No");

    OQS_SIG_free(sig);
}

int main() {
    // Define the algorithms to test
    const char *algorithms[] = { "SLH_DSA", "ML_DSA" };
    size_t num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    // Example message
    uint8_t message[] = "Este es un mensaje de prueba";
    size_t message_len = sizeof(message);

    // Test each algorithm
    for (size_t i = 0; i < num_algorithms; i++) {
        test_signature_algorithm(algorithms[i], message, message_len);
    }

    return 0;
}
