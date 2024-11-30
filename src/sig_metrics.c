#include <stdio.h>      // Para funciones de entrada y salida estándar
#include <stdlib.h>     // Para funciones de manejo de memoria y control del programa
#include <string.h>     // Para operaciones con cadenas
#include <time.h>       // Para medición del tiempo de ejecución
#include <oqs/oqs.h>    // Biblioteca para algoritmos de firma post-cuánticos (liboqs)

#define MAX_LINE_LENGTH 500000  // Tamaño máximo de cada línea de entrada

int main(int argc, char *argv[]) {
    // Validación de argumentos: Se requiere un algoritmo como parámetro
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <algorithm>\n", argv[0]);  // Mensaje de uso
        fprintf(stderr, "Available algorithms:\n");
        // Muestra todos los algoritmos de firma habilitados en liboqs
        for (size_t i = 0; i < OQS_SIG_alg_count(); i++) {
            printf("  %s\n", OQS_SIG_alg_identifier(i));
        }
        return EXIT_FAILURE;  // Termina el programa si no se proporciona el argumento correcto
    }

    // Inicialización del algoritmo de firma
    const char *alg = argv[1];  // Nombre del algoritmo proporcionado como argumento
    if (!OQS_SIG_alg_is_enabled(alg)) {
        fprintf(stderr, "Algorithm %s is not enabled in this installation of liboqs.\n", alg);
        return EXIT_FAILURE;  // Verifica si el algoritmo está habilitado en la instalación actual
    }

    OQS_SIG *sig = OQS_SIG_new(alg);  // Crea una instancia del esquema de firma
    if (sig == NULL) {
        fprintf(stderr, "Failed to initialize the signature scheme.\n");
        return EXIT_FAILURE;  // Verifica que se haya inicializado correctamente
    }

    // Reserva memoria para las claves y las firmas
    uint8_t public_key[sig->length_public_key];       // Clave pública
    uint8_t secret_key[sig->length_secret_key];       // Clave privada
    uint8_t signature[sig->length_signature];         // Firma
    size_t signature_len;                             // Longitud de la firma

    // Generación de par de claves (clave pública y privada)
    clock_t start = clock();  // Inicia el cronómetro
    if (OQS_SIG_keypair(sig, public_key, secret_key) != OQS_SUCCESS) {
        fprintf(stderr, "Keypair generation failed.\n");
        OQS_SIG_free(sig);  // Libera los recursos en caso de error
        return EXIT_FAILURE;
    }
    clock_t end = clock();  // Termina el cronómetro
    printf("%.8f\n", (double)(end - start) / CLOCKS_PER_SEC);  // Muestra el tiempo de generación de claves

    // Leer, firmar y verificar líneas desde la entrada estándar (stdin)
    char line[MAX_LINE_LENGTH];  // Buffer para almacenar cada línea de entrada
    while (fgets(line, sizeof(line), stdin) != NULL) {  // Lee línea por línea
        // Elimina el carácter de salto de línea al final de la línea, si existe
        size_t line_len = strlen(line);
        if (line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
            line_len--;
        }

        // Proceso de firma
        start = clock();  // Inicia el cronómetro
        if (OQS_SIG_sign(sig, signature, &signature_len, (uint8_t *)line, line_len, secret_key) != OQS_SUCCESS) {
            fprintf(stderr, "Signing failed for line.\n");
            break;  // Detiene el proceso si ocurre un error al firmar
        }
        end = clock();  // Termina el cronómetro
        printf("%d,%.8f,", (int)line_len, (double)(end - start) / CLOCKS_PER_SEC);  // Muestra la longitud de la línea y el tiempo de firma

        // Proceso de verificación
        start = clock();  // Inicia el cronómetro
        OQS_STATUS status = OQS_SIG_verify(sig, (uint8_t *)line, line_len, signature, signature_len, public_key);
        end = clock();  // Termina el cronómetro
        printf("%.8f\n", (double)(end - start) / CLOCKS_PER_SEC);  // Muestra el tiempo de verificación

        // Verifica si la firma es válida
        if (status != OQS_SUCCESS) {
            fprintf(stderr, "Verification failed for line.\n");
            break;  // Detiene el proceso si ocurre un error al verificar
        }
    }

    // Limpieza: libera los recursos asignados al esquema de firma
    OQS_SIG_free(sig);

    return EXIT_SUCCESS;  // Termina el programa exitosamente
}
