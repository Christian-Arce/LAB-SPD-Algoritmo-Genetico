import matplotlib.pyplot as plt

# Datos de ejemplo (reemplaza con los resultados reales)
sizes = ['Pequeño', 'Mediano', 'Grande']
sequential_times = [0.1, 1.0, 10.0]  # Reemplaza con los tiempos reales
parallel_times = [0.05, 0.5, 5.0]    # Reemplaza con los tiempos reales
num_threads = 4

# Cálculo de Speedup y Eficiencia
speedup = [seq / par for seq, par in zip(sequential_times, parallel_times)]
efficiency = [s / num_threads for s in speedup]

# Gráfico de Speedup
plt.figure()
plt.plot(sizes, speedup, marker='o', label='Speedup')
plt.xlabel('Tamaño de Datos')
plt.ylabel('Speedup')
plt.title('Speedup del Algoritmo Genético Paralelo')
plt.grid(True)
plt.legend()
plt.savefig('speedup.png')
plt.show()

# Gráfico de Eficiencia
plt.figure()
plt.plot(sizes, efficiency, marker='o', label='Eficiencia')
plt.xlabel('Tamaño de Datos')
plt.ylabel('Eficiencia')
plt.title('Eficiencia del Algoritmo Genético Paralelo')
plt.grid(True)
plt.legend()
plt.savefig('efficiency.png')
plt.show()
