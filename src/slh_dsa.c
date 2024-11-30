#include <stdio.h>
#include <oqs/oqs.h>

int main() {
    if (!OQS_SIG_alg_is_enabled(OQS_SIG_alg_sphincs_shake_128f_simple)) {
        printf("SPHINCS+ no está habilitado en esta instalación de liboqs.\n");
        return 1;
    }

    OQS_SIG *sig = OQS_SIG_new(OQS_SIG_alg_sphincs_shake_128f_simple);

    uint8_t public_key[sig->length_public_key];
    uint8_t secret_key[sig->length_secret_key];
    uint8_t signature[sig->length_signature];
    size_t signature_len;
    uint8_t message[] = "Mensaje seguro con SPHINCS+";

    OQS_SIG_keypair(sig, public_key, secret_key);
    OQS_SIG_sign(sig, signature, &signature_len, message, sizeof(message), secret_key);
    OQS_STATUS status = OQS_SIG_verify(sig, message, sizeof(message), signature, signature_len, public_key);

    printf("¿Firma válida?: %s\n", (status == OQS_SUCCESS) ? "Sí" : "No");

    OQS_SIG_free(sig);
    return 0;
}
