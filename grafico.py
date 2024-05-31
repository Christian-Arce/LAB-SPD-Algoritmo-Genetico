import matplotlib.pyplot as plt

# Datos de ejemplo (reemplaza con los resultados reales)
sizes = ['Pequeño', 'Mediano', 'Grande']
sequential_times = [0.008, 19.123, 72.728]  # tiempos secuenciales
parallel_times = [0.030, 7.520, 29.504]    # tiempos paralelos
num_threads = 16

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
