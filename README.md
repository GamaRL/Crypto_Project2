<!-- # Project 02 - Post-Quantum Cryptography

> Alumno:
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
Para configurar la aplicación, es necesario contar con la herramienta Docker instalada, y se debe configurar el módulo Docker Compose.

---

## Instalación de Docker

Para la instalación de Docker se recomienda utilizar la documentación oficial proporcionada en el siguiente link, según la distribución con la que se cuente:

https://docs.docker.com/engine/install/


## Instrucciones de Uso

### 1. Construir y ejecutar el contenedor

Para construir y ejecutar el contenedor, usa los siguientes comandos:

```bash
docker container rm crypto-02           # Elimina cualquier contenedor previo con el nombre crypto-02
docker container run -it --name crypto-02 -v ./out:/app/out crypto-debian
```

- **`docker container rm crypto-02`**: Elimina un contenedor existente llamado `crypto-02` si ya está en ejecución.
- **`docker container run -it --name crypto-02 -v ./out:/app/out crypto-debian`**: Ejecuta el contenedor en modo interactivo, con el nombre `crypto-02`, y monta el directorio local `./out` dentro del contenedor en la ruta `/app/out`. Esto permitirá que los datos generados dentro del contenedor se guarden en tu máquina local en el directorio `out/`.

### 2. Generación de Datos

Dentro del contenedor, los algoritmos criptográficos se ejecutan y los resultados generados se almacenan en el directorio `out/`. Estos resultados pueden ser usados para análisis o para alimentar otros procesos dentro de tu aplicación.

### 3. Ver los Datos Generados

Los datos generados estarán disponibles en el directorio `out/` de tu máquina local, que está vinculado al directorio `/app/out` dentro del contenedor. Puedes acceder a estos datos usando el siguiente comando:

```bash
ls ./out
```

Los archivos generados estarán dentro de esta carpeta y podrán ser utilizados según lo necesites.

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
- **out/**: Directorio local donde se almacenan los datos generados dentro del contenedor.
- **crypto-debian**: La imagen de Docker basada en Debian que ejecuta los algoritmos criptográficos.
