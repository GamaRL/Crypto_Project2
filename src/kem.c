#include <stdio.h>
#include <string.h>
#include <oqs/oqs.h>

int main() {
  if (!OQS_KEM_alg_is_enabled(OQS_KEM_alg_ml_kem_1024)) {
    printf("Kyber no está habilitado en esta instalación de liboqs.\n");
    return 1;
  }

  OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_ml_kem_1024);

  uint8_t public_key[kem->length_public_key];
  uint8_t secret_key[kem->length_secret_key];
  uint8_t ciphertext[kem->length_ciphertext];
  uint8_t shared_secret_enc[kem->length_shared_secret];
  uint8_t shared_secret_dec[kem->length_shared_secret];

  OQS_KEM_keypair(kem, public_key, secret_key);
  OQS_KEM_encaps(kem, ciphertext, shared_secret_enc, public_key);
  OQS_KEM_decaps(kem, shared_secret_dec, ciphertext, secret_key);

  printf("¿Claves compartidas iguales?: %s\n",
      (memcmp(shared_secret_enc, shared_secret_dec, kem->length_shared_secret) == 0) ? "Sí" : "No");

  OQS_KEM_free(kem);
  return 0;
}
