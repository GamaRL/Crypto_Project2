#!/bin/bash

rm -f out/*

./scripts/generate_random_strings.sh

echo "Testing Dilithium2..."
./sig_metrics "Dilithium2" < random_strings.txt > out/dilithium_2.csv
echo "Testing Dilithium3..."
./sig_metrics "Dilithium3" < random_strings.txt > out/dilithium_3.csv
echo "Testing Dilithium5..."
./sig_metrics "Dilithium5" < random_strings.txt > out/dilithium_5.csv

echo "Testing SPHINCS+-SHAKE-128s-simple..."
./sig_metrics "SPHINCS+-SHAKE-128s-simple" < random_strings.txt > out/sphincs_128s.csv
echo "Testing SPHINCS+-SHAKE-128f-simple..."
./sig_metrics "SPHINCS+-SHAKE-128f-simple" < random_strings.txt > out/sphincs_128f.csv
echo "Testing SPHINCS+-SHAKE-192s-simple..."
./sig_metrics "SPHINCS+-SHAKE-192s-simple" < random_strings.txt > out/sphincs_192s.csv
echo "Testing SPHINCS+-SHAKE-192f-simple..."
./sig_metrics "SPHINCS+-SHAKE-192f-simple" < random_strings.txt > out/sphincs_192f.csv
echo "Testing SPHINCS+-SHAKE-256s-simple..."
./sig_metrics "SPHINCS+-SHAKE-256s-simple" < random_strings.txt > out/sphincs_256s.csv
echo "Testing SPHINCS+-SHAKE-256f-simple..."
./sig_metrics "SPHINCS+-SHAKE-256f-simple" < random_strings.txt > out/sphincs_256f.csv

./scripts/format_metric_files.sh

echo "Testing ML-KEM-512..."
./kem_metrics "ML-KEM-512" > out/kem.csv
echo "Testing ML-KEM-768..."
./kem_metrics "ML-KEM-768" >> out/kem.csv
echo "Testing ML-KEM-1024..."
./kem_metrics "ML-KEM-1024" >> out/kem.csv


echo "Generating plots..."
ALGORITHM='dilithium_2' gnuplot scripts/plots/get_plots.gp
ALGORITHM='dilithium_3' gnuplot scripts/plots/get_plots.gp
ALGORITHM='dilithium_5' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_128s' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_128f' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_192s' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_192f' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_256s' gnuplot scripts/plots/get_plots.gp
ALGORITHM='sphincs_256f' gnuplot scripts/plots/get_plots.gp


gnuplot scripts/plots/get_kem_plot.gp
gnuplot scripts/plots/get_sig_key_time_plot.gp
