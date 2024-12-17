import matplotlib.pyplot as plt

# Temps d'exécution

# Multiplication petites tailles
multiplication_petites_tailles_sizes = [i for i in range(2, 65)]
multiplication_petites_tailles_naive = [0.400000, 0.760000, 0.220000, 0.290000, 0.330000, 0.400000, 0.530000, 0.580000, 0.960000, 1.740000, 1.440000, 1.510000, 1.860000, 2.340000, 2.730000, 3.220000, 4.460000, 4.920000, 6.470000, 6.480000, 7.500000, 8.440000, 10.370000, 10.990000, 12.290000, 14.250000, 15.660000, 17.290000, 23.600000, 25.970000, 22.870000, 25.110000, 27.190000, 33.740000, 32.350000, 37.000000, 41.980000, 45.550000, 48.820000, 48.030000, 60.410000, 56.280000, 65.160000, 63.830000, 80.190000, 89.950000, 78.700000, 101.180000, 97.650000, 97.360000, 102.010000, 108.200000, 130.940000, 136.490000, 136.610000, 138.120000, 144.970000, 154.360000, 157.760000, 178.710000, 225.770000, 241.990000, 205.420000]
multiplication_petites_tailles_strassen200 = [0.390000, 1.890000, 0.480000, 4.990000, 4.090000, 1.570000, 0.980000, 60.670000, 57.410000, 56.290000, 46.390000, 47.030000, 28.930000, 12.990000, 4.470000, 455.820000, 465.150000, 450.710000, 446.300000, 448.350000, 329.260000, 335.950000, 312.780000, 293.800000, 205.680000, 225.160000, 94.540000, 173.730000, 40.330000, 70.120000, 28.780000, 972.820000, 2137.040000, 2985.280000, 4093.370000, 4043.890000, 4528.270000, 3786.550000, 2980.210000, 2696.400000, 2073.270000, 2291.710000, 2278.640000, 2288.260000, 2200.960000, 2063.330000, 1685.240000, 1744.320000, 1637.310000, 1587.500000, 1592.360000, 1490.280000, 688.670000, 890.090000, 282.070000, 595.940000, 298.710000, 596.640000, 268.350000, 492.400000, 430.400000, 405.220000, 217.120000]
multiplication_petites_tailles_strassen128 = [0.440000, 0.940000, 0.630000, 4.420000, 4.180000, 1.720000, 1.000000, 73.310000, 57.920000, 54.680000, 47.220000, 43.700000, 27.430000, 20.190000, 4.570000, 481.960000, 535.400000, 448.600000, 395.510000, 361.600000, 431.280000, 331.360000, 365.200000, 284.330000, 54.810000, 217.070000, 112.520000, 151.890000, 39.200000, 66.150000, 28.180000, 803.770000, 1831.780000, 2949.210000, 4589.220000, 4122.580000, 4576.030000, 3739.250000, 3037.920000, 2903.970000, 2005.030000, 2449.600000, 2523.070000, 2496.860000, 1801.080000, 1943.160000, 1732.560000, 1655.280000, 1735.970000, 1828.110000, 1785.140000, 1919.090000, 1490.640000, 1277.410000, 765.520000, 845.310000, 414.700000, 608.830000, 278.400000, 393.410000, 415.600000, 384.780000, 212.360000]
multiplication_petites_tailles_strassen64 = [0.540000, 1.650000, 0.490000, 5.110000, 4.070000, 2.010000, 0.950000, 67.250000, 59.240000, 60.570000, 48.340000, 45.350000, 29.770000, 18.270000, 4.690000, 460.950000, 593.180000, 482.680000, 444.620000, 399.390000, 406.270000, 345.900000, 347.020000, 289.310000, 55.970000, 228.740000, 253.820000, 152.310000, 38.170000, 73.920000, 27.690000, 832.190000, 1753.060000, 2501.190000, 3155.010000, 3590.430000, 3469.750000, 3065.820000, 2985.060000, 2594.560000, 2281.030000, 2338.540000, 2219.950000, 2029.510000, 2278.110000, 2172.620000, 1627.790000, 1807.530000, 1865.170000, 1795.970000, 1544.000000, 1598.730000, 1176.380000, 1016.240000, 573.330000, 719.400000, 331.930000, 586.090000, 761.750000, 359.670000, 244.750000, 227.170000, 212.840000]

# Temps de multiplication
multiplication_sizes = [2**i for i in range(1, 11)]  # Puissances de 2
multiplication_naive = [0.325000, 0.375000, 0.800000, 4.375000, 36.925000, 320.325000, 2132.550000, 16848.375000, 140860.475000, 1839057.200000]
multiplication_strassen256 = [0.525000, 0.600000, 1.150000, 5.550000, 31.050000, 249.975000, 2146.875000, 17237.425000, 127127.475000, 850878.350000]
multiplication_strassen128 = [0.450000, 0.600000, 1.150000, 5.150000, 31.800000, 240.025000, 2095.100000, 13874.975000, 103070.125000, 746607.150000]
multiplication_strassen64 = [0.525000, 0.675000, 1.200000, 5.650000, 31.050000, 251.150000, 1710.750000, 12420.800000, 97473.175000, 675253.825000]
multiplication_strassen32 = [0.425000, 0.625000, 1.400000, 5.950000, 33.250000, 248.550000, 1778.250000, 12150.550000, 91942.625000, 703657.575000]
multiplication_strassen16 = [0.625000, 0.650000, 1.300000, 6.250000, 44.650000, 330.500000, 2410.300000, 17252.250000, 123208.625000, 921874.525000]
#multiplication_strassen8 = [1.300000, 0.700000, 1.300000, 9.875000, 74.125000, 536.175000, 4401.975000, 28659.300000, 203640.950000, 1444500.975000]

# Temps d'inversion
inversion_sizes = [2**i for i in range(1, 11)]
inversion_pluq = [1.866667, 5.066667, 20.333333, 89.533333, 397.166667, 1981.266667, 14301.533333, 92471.733333, 651789.033333, 6522266.100000]
inversion_strassen_naive = [3.900000, 3.933333, 9.566667, 22.966667, 75.100000, 364.100000, 2245.566667, 20666.300000, 162897.700000, 1313880.766667]
inversion_strassen_strassen64 = [6.900000, 10.266667, 15.266667, 30.166667, 102.466667, 453.133333, 2883.033333, 17410.966667, 138026.600000, 1067899.800000]


# Graphique pour la multiplication petites tailles
plt.figure(figsize=(10, 5))
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_naive, label="Naive Multiplication", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen200, label="Strassen Multiplication Limite=200", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen128, label="Strassen Multiplication Limite=128", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen64, label="Strassen Multiplication Limite=64", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Multiplication Petites Tailles")
plt.legend()
plt.grid(True)
plt.show()

# Graphique pour la multiplication Strassen avec limites différentes
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_strassen256, label="Multiplication Strassen Limite=256", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen128, label="Multiplication Strassen Limite=128", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen64, label="Multiplication Strassen Limite=64", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen32, label="Multiplication Strassen Limite=32", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen16, label="Multiplication Strassen Limite=16", marker='o')
#plt.plot(multiplication_sizes, multiplication_strassen8, label="Multiplication Strassen Limite=8", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution - Multiplication Strassen, limites différentes")
plt.legend()
plt.grid(True)
plt.show()

# Graphique pour la multiplication naïve et strassen
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_naive, label="Multiplication Naive", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen64, label="Multiplication Strassen Limite=64", marker='o')
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Multiplication naïve vs Strassen (échelle logarithmique)")
plt.legend()
plt.grid(True)
plt.show()

# Graphique pour l'inversion
plt.figure(figsize=(10, 5))
plt.plot(inversion_sizes, inversion_pluq, label="Inversion PLUQ", marker='o')
plt.plot(inversion_sizes, inversion_strassen_naive, label="Inversion Strassen Naive", marker='o')
plt.plot(inversion_sizes, inversion_strassen_strassen64, label="Inversion Strassen Strassen Limite=64", marker='o')
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution - Inversions (échelle logarithmique)")
plt.legend()
plt.grid(True)
plt.show()





# Mémoire

# Multiplications petites tailles
multiplication_petites_tailles_sizes = [i for i in range(2, 65)]
multiplication_petites_tailles_naive_memory = [0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000]
multiplication_petites_tailles_strassen200_memory = [101.600000, 96.000000, 101.200000, 96.000000, 96.000000, 96.000000, 110.000000, 108.000000, 109.600000, 107.200000, 100.400000, 106.400000, 106.400000, 106.400000, 131.600000, 102.400000, 102.400000, 101.200000, 102.800000, 102.000000, 100.800000, 102.800000, 104.000000, 99.200000, 103.200000, 102.800000, 101.600000, 99.600000, 98.800000, 101.200000, 146.800000, 98.400000, 98.800000, 99.600000, 99.200000, 97.200000, 101.200000, 98.400000, 100.000000, 98.800000, 101.200000, 97.600000, 99.200000, 100.800000, 98.800000, 97.600000, 99.200000, 99.600000, 98.800000, 97.600000, 98.800000, 98.000000, 99.600000, 99.200000, 97.200000, 98.000000, 98.800000, 97.600000, 100.000000, 100.000000, 98.800000, 97.600000, 191.200000]
multiplication_petites_tailles_strassen128_memory = [102.000000, 96.400000, 101.600000, 96.400000, 96.000000, 96.000000, 111.200000, 105.600000, 108.400000, 106.800000, 101.200000, 104.800000, 104.000000, 105.200000, 130.000000, 100.400000, 110.400000, 108.000000, 102.000000, 102.400000, 107.600000, 97.600000, 99.200000, 103.600000, 103.200000, 100.400000, 101.600000, 100.800000, 100.400000, 101.600000, 149.200000, 97.600000, 98.800000, 100.000000, 100.400000, 96.400000, 101.200000, 99.200000, 98.800000, 98.400000, 99.200000, 96.400000, 98.800000, 100.000000, 98.800000, 97.200000, 98.000000, 98.400000, 98.400000, 97.200000, 98.400000, 99.600000, 102.000000, 98.400000, 99.200000, 99.600000, 96.400000, 96.800000, 98.800000, 99.600000, 96.400000, 96.000000, 190.000000]
multiplication_petites_tailles_strassen64_memory = [102.000000, 98.000000, 103.600000, 97.200000, 96.000000, 96.000000, 110.400000, 103.200000, 110.400000, 107.200000, 102.800000, 106.400000, 103.200000, 106.400000, 130.400000, 101.600000, 102.400000, 104.400000, 99.600000, 107.200000, 102.000000, 97.600000, 104.400000, 105.600000, 100.000000, 98.400000, 98.400000, 98.800000, 99.200000, 101.200000, 146.800000, 99.200000, 99.200000, 99.200000, 98.400000, 97.600000, 113.600000, 98.000000, 99.600000, 98.400000, 99.600000, 97.200000, 99.200000, 99.600000, 99.200000, 96.000000, 99.600000, 99.600000, 98.800000, 97.200000, 99.200000, 98.400000, 100.400000, 98.000000, 112.000000, 96.800000, 100.800000, 96.800000, 100.400000, 98.000000, 97.600000, 96.400000, 192.400000]

# Multiplications grandes tailles
multiplication_sizes = [2**i for i in range(1, 11)]
multiplication_naive_memory = [0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000]
multiplication_strassen256_memory = [101.600000, 101.600000, 111.200000, 128.400000, 153.200000, 199.600000, 282.000000, 97.200000, 713.200000, 4990.800000]
multiplication_strassen128_memory = [101.600000, 101.200000, 110.000000, 130.000000, 152.000000, 189.200000, 283.200000, 725.200000, 5034.800000, 35126.400000]
multiplication_strassen64_memory = [101.600000, 101.200000, 110.800000, 129.600000, 150.400000, 192.000000, 902.800000, 5167.200000, 35668.400000, 250937.200000]
multiplication_strassen32_memory = [101.600000, 103.200000, 113.600000, 124.800000, 150.400000, 746.000000, 5258.000000, 36696.800000, 257893.200000, 1809366.400000]
multiplication_strassen16_memory = [101.600000, 106.400000, 114.800000, 121.200000, 752.400000, 5620.000000, 38699.200000, 271755.600000, 1903976.000000, 13381019.200000]
#multiplication_strassen8_memory = [101.600000, 112.000000, 112.400000, 772.400000, 5174.400000, 36164.800000, 250319.600000, 1733954.400000, 12293639.600000, 86057532.400000]

# Inversions
taille_inversion = [2**i for i in range(1, 11)]
inversion_pluq_memory = [828.266667, 1457.066667, 3644.800000, 11076.800000, 38242.133333, 141725.333333, 545301.866667, 2138444.800000, 8470880.000000, 33718563.200000]
inversion_strassen_naive_memory = [837.333333, 1893.333333, 4194.666667, 8802.133333, 18018.666667, 36508.266667, 73408.000000, 147281.066667, 294893.333333, 590621.333333]
inversion_strassen_strassen64_memory = [810.666667, 2526.400000, 4795.200000, 9396.800000, 18618.133333, 37073.600000, 74102.933333, 152454.400000, 326541.866667, 806168.000000]


# Multiplication petites tailles (mémoire)
plt.figure(figsize=(10, 5))
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_naive_memory, label="Naive Multiplication", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen200_memory, label="Strassen Multiplication Limite=200", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen128_memory, label="Strassen Multiplication Limite=128", marker='o')
plt.scatter(multiplication_petites_tailles_sizes, multiplication_petites_tailles_strassen64_memory, label="Strassen Multiplication Limite=64", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Mémoire Utilisée (kB)")
plt.title("Mémoire Utilisée - Multiplication Petites Tailles")
plt.legend()
plt.grid(True)
plt.show()

# Multiplication Strassen grandes tailles avec limites différentes
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_strassen256_memory, label="Strassen Multiplication Limite=256", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen128_memory, label="Strassen Multiplication Limite=128", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen64_memory, label="Strassen Multiplication Limite=64", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen32_memory, label="Strassen Multiplication Limite=32", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen16_memory, label="Strassen Multiplication Limite=16", marker='o')
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Mémoire Utilisée (kB)")
plt.title("Mémoire Utilisée - Multiplication Strassen, limites différentes (échelle logarihmique)")
plt.legend()
plt.grid(True)
plt.show()

# Comparaison Naive et Strassen pour les grandes tailles (mémoire)
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_naive_memory, label="Naive Multiplication", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen64_memory, label="Strassen Multiplication Limite=64", marker='o')
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Mémoire Utilisée (kB)")
plt.title("Mémoire Utilisée - Multiplication Naive vs Strassen (échelle logarihmique)")
plt.legend()
plt.grid(True)
plt.show()

# Comparaison pour les inversions
plt.figure(figsize=(10, 5))
plt.plot(taille_inversion, inversion_pluq_memory, label="Inversion PLUQ", marker='o')
plt.plot(taille_inversion, inversion_strassen_naive_memory, label="Inversion Strassen Naive", marker='o')
plt.plot(taille_inversion, inversion_strassen_strassen64_memory, label="Inversion Strassen Strassen (Limite=64)", marker='o')
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Mémoire Utilisée (kB)")
plt.title("Mémoire Utilisée - Inversions (échelle logarihmique)")
plt.legend()
plt.grid(True)
plt.show()
