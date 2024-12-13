import matplotlib.pyplot as plt

# Multiplication petites tailles
multiplication_petites_tailles_sizes = [i for i in range(2, 65)]
multiplication_petites_tailles_naive = [0.320000, 0.470000, 0.350000, 0.390000, 0.490000, 0.610000, 0.780000, 0.930000, 1.160000, 1.590000, 2.100000, 2.500000, 2.990000, 3.770000, 4.390000, 5.190000, 6.950000, 7.440000, 8.460000, 11.230000, 12.090000, 13.440000, 14.030000, 14.580000, 15.130000, 16.100000, 18.140000, 20.190000, 28.200000, 30.840000, 25.910000, 29.010000, 31.350000, 36.600000, 40.210000, 40.250000, 46.690000, 50.720000, 51.480000, 53.160000, 59.140000, 58.550000, 66.660000, 66.400000, 83.010000, 91.470000, 81.810000, 86.380000, 91.630000, 96.420000, 101.860000, 108.280000, 130.910000, 135.760000, 136.670000, 139.110000, 144.930000, 155.110000, 164.590000, 185.740000, 229.170000, 241.940000, 202.600000]
multiplication_petites_tailles_strassen = [0.420000, 1.240000, 0.480000, 3.780000, 3.500000, 1.730000, 0.970000, 58.680000, 56.700000, 54.980000, 47.590000, 47.540000, 28.730000, 12.430000, 4.600000, 475.310000, 480.510000, 473.290000, 448.340000, 414.660000, 336.780000, 344.040000, 313.210000, 294.430000, 206.310000, 244.460000, 100.870000, 174.600000, 46.840000, 78.060000, 28.600000, 993.580000, 2083.270000, 2981.450000, 4142.290000, 3793.540000, 4384.960000, 3709.980000, 3023.340000, 2662.230000, 2114.540000, 2133.350000, 2189.990000, 2215.060000, 1912.390000, 2060.670000, 1616.090000, 1782.630000, 1714.920000, 1533.850000, 1617.510000, 1475.250000, 659.240000, 872.670000, 277.480000, 585.790000, 289.930000, 596.400000, 269.900000, 481.590000, 413.250000, 402.000000, 212.530000]

# Temps de multiplication
multiplication_sizes = [2**i for i in range(1, 11)]  # Puissances de 2
multiplication_naive = [0.200000, 0.233333, 0.500000, 2.733333, 23.566667, 207.600000, 1889.700000, 16190.600000, 137398.266667, 2002429.100000]
multiplication_strassen = [0.533333, 0.666667, 1.133333, 5.200000, 30.400000, 221.800000, 2058.266667, 14768.933333, 105523.633333, 749496.533333]

# Temps d'inversion
inversion_sizes = [2**i for i in range(1, 11)]
inversion_pluq = [1.566667, 3.733333, 26.766667, 80.400000, 326.833333, 1810.300000, 13790.466667, 92414.700000, 548672.933333, 5963250.066667]
inversion_strassen_naive = [3.766667, 3.666667, 8.400000, 22.100000, 70.533333, 330.033333, 2230.233333, 18971.866667, 160634.100000, 1329140.833333]
inversion_strassen_strassen = [8.266667, 6.433333, 10.900000, 37.633333, 86.633333, 405.333333, 2408.633333, 20266.700000, 147229.166667, 1140833.900000]


# Graphique pour la multiplication petites tailles
plt.figure(figsize=(10, 5))
plt.plot(multiplication_petites_tailles_sizes, multiplication_petites_tailles_naive, label="Naive Multiplication", marker='o')
plt.plot(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen, label="Strassen Multiplication", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Multiplication Petites Tailles")
plt.legend()
plt.grid(True)
plt.show()

# Graphique pour la multiplication grandes tailles
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_naive, label="Multiplication Naive", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen, label="Multiplication Strassen", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Multiplication Grandes Tailles")
plt.legend()
plt.grid(True)
plt.show()

# Graphique pour l'inversion
plt.figure(figsize=(10, 5))
plt.plot(inversion_sizes, inversion_pluq, label="Inversion PLUQ", marker='o')
plt.plot(inversion_sizes, inversion_strassen_naive, label="Inversion Strassen Naive", marker='o')
plt.plot(inversion_sizes, inversion_strassen_strassen, label="Inversion Strassen Strassen", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Inversion")
plt.legend()
plt.grid(True)
plt.show()
