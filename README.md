# Project 02 - Post-Quantum Cryptography

> Alumnos:
> - Coria Martínez, Gustavo      - 318164838
> - García Lemus, Rocío			     - 318263254
> - Morales Zilli, Luis Fernando - 421085620
> - Organista Álvarez, Ricardo	 - 421018596
> - Ríos Lira, Gamaliel 			   - 115002126
>
> Materia: Criptografía
>
> Semestre: 2025-1

##
# Configuración de la aplicación
Para configurar la aplicación, es necesario contar con la herramienta Docker instalada.

---

## Instalación de Docker

Para la instalación de Docker se recomienda utilizar la documentación oficial proporcionada en el siguiente link, según la distribución con la que se cuente:

https://docs.docker.com/engine/install/


## Instrucciones de Uso

### 1. Construir y ejecutar el contenedor

Antes de cualquier cosa, es importante generar el directorio `out/`:
```bash
mkdir out/
```

En este directorio se cargarán todos los datos de salida de la ejecución de los programas implementados.

Para construir y ejecutar el contenedor, se pueden usar los siguientes comandos:

```bash
docker build -t crypto-debian .
docker container rm crypto-02           # Elimina cualquier contenedor previo con el nombre crypto-02
docker container run -it --name crypto-02 -v ./out:/app/out crypto-debian
```

- **`docker build -t crypto-debian .`**: Crea una imagen llamada crypto-debian, la cual empaqueta los programas que se desarrollaron para probar los algoritmos.
- **`docker container rm crypto-02`**: Elimina un contenedor existente llamado `crypto-02` si ya está en ejecución.
- **`docker container run -it --name crypto-02 -v ./out:/app/out crypto-debian`**: Ejecuta el contenedor en modo interactivo, con el nombre `crypto-02`, y monta el directorio local `./out` dentro del contenedor en la ruta `/app/out`. Esto permitirá que los datos generados dentro del contenedor se guarden en tu máquina local en el directorio `out/`.

### 2. Generación de Datos

Dentro del contenedor, los algoritmos criptográficos se ejecutan y los resultados generados se almacenan en el directorio `out/`. Estos resultados pueden ser usados para análisis o para alimentar otros procesos dentro de tu aplicación.

### 3. Ver los Datos Generados

Los datos generados estarán disponibles en el directorio `out/` de tu máquina local, que está vinculado al directorio `/app/out` dentro del contenedor. Se puede acceder a estos datos usando el siguiente comando:

```bash
ls ./out
```

Los archivos generados estarán dentro de esta carpeta y podrán ser utilizados según se necesite. El comano anterior debe mostrar tanto archivos `.csv` como archivos `.png` con las gráficas.

### 4. Detener el Contenedor

Cuando hayas terminado de usar el contenedor, puedes detenerlo con:

```bash
docker container stop crypto-02
```

### 5. Eliminar el Contenedor

Si deseas eliminar el contenedor después de usarlo, puedes hacerlo con:

```bash
docker container rm crypto-02
```

## Estructura de Archivos

- **Dockerfile**: Define la configuración y los pasos necesarios para construir la imagen Docker.
- **src/**: Contiene los programas implementados haciendo uso de la biblioteca `liboqs`, estos programas sacan las métricas.
- **scripts/**: Contiene algunos programas en **Bash** para automatizar la interpretación de los datos y la generación de gráficas con **GNUPlot**.
- **out/**: Directorio local donde se almacenan los datos generados dentro del contenedor.
- **crypto-debian**: La imagen de Docker basada en Debian que ejecuta los algoritmos criptográficos.
