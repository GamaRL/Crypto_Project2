#include <stdio.h>      // Para funciones de entrada/salida
#include <stdlib.h>     // Para funciones de control del programa, como exit()
#include <string.h>     // Para manipulación de cadenas
#include <time.h>       // Para medición del tiempo de ejecución
#include <oqs/oqs.h>    // Biblioteca de algoritmos post-cuánticos (liboqs)

#define NUM_ITERATIONS 100  // Número de iteraciones para medir tiempos promedio

int main(int argc, char *argv[]) {
    // Validación de los argumentos: se requiere un algoritmo como parámetro
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <algorithm>\n", argv[0]);  // Mensaje de error
        fprintf(stderr, "Available algorithms:\n");
        // Muestra todos los algoritmos KEM habilitados en la instalación actual de liboqs
        for (size_t i = 0; i < OQS_KEM_alg_count(); i++) {
            printf("  %s\n", OQS_KEM_alg_identifier(i));
        }
        return EXIT_FAILURE;  // Termina el programa con error
    }

    // Asigna el nombre del algoritmo proporcionado por el usuario
    const char *alg = argv[1];

    // Verifica si el algoritmo especificado está habilitado
    if (!OQS_KEM_alg_is_enabled(alg)) {
        fprintf(stderr, "Algorithm %s is not enabled in this installation of liboqs.\n", alg);
        return EXIT_FAILURE;
    }

    // Inicializa el algoritmo KEM especificado
    OQS_KEM *kem = OQS_KEM_new(alg);

    // Reserva memoria para las claves, texto cifrado y secretos compartidos
    uint8_t public_key[kem->length_public_key];       // Clave pública
    uint8_t secret_key[kem->length_secret_key];       // Clave privada
    uint8_t ciphertext[kem->length_ciphertext];       // Texto cifrado
    uint8_t shared_secret_enc[kem->length_shared_secret]; // Secreto compartido (encapsulado)
    uint8_t shared_secret_dec[kem->length_shared_secret]; // Secreto compartido (desencapsulado)

    // Variables para acumular los tiempos de ejecución
    double key_gen_time = 0.0;  // Tiempo de generación de claves
    double encaps_time  = 0.0;  // Tiempo de encapsulación
    double decaps_time  = 0.0;  // Tiempo de desencapsulación

    // Bucle para realizar las pruebas NUM_ITERATIONS veces
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Medición del tiempo de generación de claves
        clock_t start = clock();
        OQS_KEM_keypair(kem, public_key, secret_key);  // Genera el par de claves
        clock_t end = clock();
        key_gen_time += (double)(end - start) / CLOCKS_PER_SEC;  // Acumula el tiempo

        // Medición del tiempo de encapsulación
        start = clock();
        OQS_KEM_encaps(kem, ciphertext, shared_secret_enc, public_key);  // Genera el texto cifrado y el secreto compartido
        end = clock();
        encaps_time += (double)(end - start) / CLOCKS_PER_SEC;  // Acumula el tiempo

        // Medición del tiempo de desencapsulación
        start = clock();
        OQS_KEM_decaps(kem, shared_secret_dec, ciphertext, secret_key);  // Recupera el secreto compartido
        end = clock();
        decaps_time += (double)(end - start) / CLOCKS_PER_SEC;  // Acumula el tiempo

        // Verificación: compara los secretos generados y recuperados
        if (memcmp(shared_secret_enc, shared_secret_dec, kem->length_shared_secret) != 0) {
            fprintf(stderr, "Verification failed for algorithm %s.\n", alg);
            return EXIT_FAILURE;
        }
    }

    // Calcula los tiempos promedio dividiendo por el número de iteraciones
    key_gen_time /= NUM_ITERATIONS;
    encaps_time  /= NUM_ITERATIONS;
    decaps_time  /= NUM_ITERATIONS;

    // Imprime los resultados en formato CSV: algoritmo, tiempo de generación, encapsulación y desencapsulación
    printf("%s,%.8f,%.8f,%.8f\n", alg, key_gen_time, encaps_time, decaps_time);

    // Libera los recursos asignados al algoritmo KEM
    OQS_KEM_free(kem);

    return EXIT_SUCCESS;  // Termina el programa exitosamente
}
