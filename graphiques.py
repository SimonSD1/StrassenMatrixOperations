import matplotlib.pyplot as plt

# Données simulées (remplacez par vos propres résultats)
# Temps de multiplication
multiplication_sizes = [2**i for i in range(1, 11)]  # Puissances de 2
multiplication_naive = [0.200000, 0.233333, 0.500000, 2.733333, 23.566667, 207.600000, 1889.700000, 16190.600000, 137398.266667, 2002429.100000]
multiplication_strassen = [0.533333, 0.666667, 1.133333, 5.200000, 30.400000, 221.800000, 2058.266667, 14768.933333, 105523.633333, 749496.533333]

# Temps d'inversion
inversion_sizes = [2**i for i in range(1, 11)]
inversion_pluq = [1.566667, 3.733333, 26.766667, 80.400000, 326.833333, 1810.300000, 13790.466667, 92414.700000, 548672.933333, 5963250.066667]
inversion_strassen_naive = [3.766667, 3.666667, 8.400000, 22.100000, 70.533333, 330.033333, 2230.233333, 18971.866667, 160634.100000, 1329140.833333]
inversion_strassen_strassen = [8.266667, 6.433333, 10.900000, 37.633333, 86.633333, 405.333333, 2408.633333, 20266.700000, 147229.166667, 1140833.900000]

# Graphique pour la multiplication
plt.figure(figsize=(10, 5))
plt.plot(multiplication_sizes, multiplication_naive, label="Multiplication Naive", marker='o')
plt.plot(multiplication_sizes, multiplication_strassen, label="Multiplication Strassen", marker='o')
plt.xlabel("Taille des Matrices (NxN)")
plt.ylabel("Temps d'exécution (ms)")
plt.title("Temps d'Execution Multiplication")
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
