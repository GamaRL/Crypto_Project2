# Start from the official Debian base image
FROM debian:latest

# Update and upgrade the system packages
RUN apt update
RUN apt upgrade -y

RUN apt install -y git astyle cmake gcc ninja-build libssl-dev python3-pytest \
python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind \
gnuplot


# Compiling LIBOQS
WORKDIR /liboqs
RUN git clone https://github.com/open-quantum-safe/liboqs.git .
RUN mkdir build
WORKDIR /liboqs/build
RUN cmake \
-DOQS_MINIMAL_BUILD="KEM_ml_kem_512;KEM_ml_kem_768;KEM_ml_kem_1024;SIG_sphincs_shake_128s_simple;SIG_sphincs_shake_192s_simple;SIG_sphincs_shake_256s_simple;SIG_sphincs_shake_128f_simple;SIG_sphincs_shake_192f_simple;SIG_sphincs_shake_256f_simple;SIG_dilithium_2;SIG_dilithium_3;SIG_dilithium_5" \
-GNinja ..
RUN ninja
RUN ninja install

# Running algorithms' tests
COPY ./src /app
COPY ./random_strings.txt /app/random_strings.txt
COPY ./get_metrics.sh /app/get_metrics.sh
COPY ./format_metrics.sh /app/format_metrics.sh
COPY ./get_plots.gp /app/get_plots.gp
COPY ./get_columns.gp /app/get_columns.gp
COPY ./get_columns2.gp /app/get_columns2.gp
WORKDIR /app

# Compiling
RUN gcc sig_metrics.c -o sig_metrics -loqs -lcrypto -lssl
RUN gcc kem_metrics.c -o kem_metrics -loqs -lcrypto -lssl

# Set a default command (optional)
CMD ["./get_metrics.sh"]
