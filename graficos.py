import matplotlib.pyplot as plt

# Dados de entrada (elementos, tempo de execução, etc.)
algorithms = ['Bubble Sort', 'Improved Bubble Sort', 'Insertion Sort', 'Selection Sort', 'Heap Sort', 'Radix Sort', 'Merge Sort', 'Quick Sort']
sizes = [1000, 10000, 100000]

# Dados para o gráfico (tempo de execução em milissegundos para Best Case, Average Case e Worst Case)
# [algoritmo][caso][tamanho]
times = {
    'Bubble Sort': {'Best': [2, 194, 26197], 'Average': [3, 443, 43422], 'Worst': [4, 367, 39320]},
    'Improved Bubble Sort': {'Best': [0, 0, 0], 'Average': [3, 468, 47894], 'Worst': [4, 394, 39188]},
    'Insertion Sort': {'Best': [0, 0, 1], 'Average': [2, 138, 11740], 'Worst': [2, 230, 20753]},
    'Selection Sort': {'Best': [1, 158, 17343], 'Average': [1, 176, 17236], 'Worst': [1, 168, 15748]},
    'Heap Sort': {'Best': [0, 3, 28], 'Average': [0, 2, 41], 'Worst': [0, 3, 28]}, 
    'Radix Sort': {'Best': [0, 2, 19], 'Average': [0, 1, 15], 'Worst': [0, 2, 20]},
    'Merge Sort': {'Best': [0, 1, 15], 'Average': [1, 3, 24], 'Worst': [1, 1, 13]},
    'Quick Sort': {'Best': [0, 1, 8], 'Average': [0, 2, 18], 'Worst': [0, 1, 16]}
}

# Função para gerar os gráficos
def plot_sorting_times():
    for algorithm in algorithms:
        best_times = times[algorithm]['Best']
        average_times = times[algorithm]['Average']
        worst_times = times[algorithm]['Worst']
        
        plt.figure(figsize=(8, 6))
        plt.plot(sizes, best_times, label='Best Case', marker='o')
        plt.plot(sizes, average_times, label='Average Case', marker='o')
        plt.plot(sizes, worst_times, label='Worst Case', marker='o')
        
        plt.title(f'{algorithm} - Execution Time vs. Number of Elements')
        plt.xlabel('Number of Elements')
        plt.ylabel('Execution Time (ms)')
        plt.xticks(sizes)
        plt.legend()
        plt.grid(True)
        
        plt.show()

# Gerar os gráficos
plot_sorting_times()
