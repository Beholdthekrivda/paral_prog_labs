import matplotlib.pyplot as plt
import numpy as np

# Данные из таблицы
processes = np.array([1, 2, 4, 8, 12, 16, 20, 24, 32])
time = np.array([4.69745, 2.26389, 1.19527, 0.631331, 0.421325, 
                 0.31645, 0.25438, 0.387548, 0.468701])
speedup = np.array([1, 2.07494622088529, 3.930032544948, 7.44055020266706, 
                    11.1492315908147, 14.8442091957655, 18.4662709332495, 
                    12.1209501790746, 10.0222743284098])
efficiency = np.array([1, 1.03747311044265, 0.982508136237001, 0.930068775333383, 
                       0.929102632567891, 0.927763074735345, 0.923313546662473, 
                       0.505039590794775, 0.313196072762806])

# Настройка для отображения кириллицы
plt.rcParams['font.sans-serif'] = ['DejaVu Sans', 'Arial', 'Liberation Sans']
plt.rcParams['axes.unicode_minus'] = False

# Создание фигуры с 3 графиками
fig, axes = plt.subplots(1, 3, figsize=(18, 6))

# --- График 1: Время выполнения ---
axes[0].plot(processes, time, marker='o', color='blue', linewidth=2, markersize=6)

axes[0].set_title('Время выполнения', fontsize=14, fontweight='bold')
axes[0].set_xlabel('Количество процессов (p)', fontsize=12)
axes[0].set_ylabel('Время (сек)', fontsize=12)
axes[0].grid(True, linestyle=':', alpha=0.7)
axes[0].set_xticks(processes)

# --- График 2: Ускорение ---
axes[1].plot(processes, speedup, marker='o', color='red', linewidth=2, markersize=6)
axes[1].plot(processes, processes, linestyle='--', color='gray', label='Идеальное (S=p)', linewidth=1.5)

axes[1].set_title('Ускорение (Speedup)', fontsize=14, fontweight='bold')
axes[1].set_xlabel('Количество процессов (p)', fontsize=12)
axes[1].set_ylabel('S_p = T_1/T_p', fontsize=12)
axes[1].legend(fontsize=9)
axes[1].grid(True, linestyle=':', alpha=0.7)
axes[1].set_xticks(processes)

# --- График 3: Эффективность ---
axes[2].plot(processes, efficiency, marker='o', color='green', linewidth=2, markersize=6)
axes[2].axhline(y=1, linestyle='--', color='gray', label='Идеальная (E=1)', linewidth=1.5)

axes[2].set_title('Эффективность (Efficiency)', fontsize=14, fontweight='bold')
axes[2].set_xlabel('Количество процессов (p)', fontsize=12)
axes[2].set_ylabel('E_p = S_p/p', fontsize=12)
axes[2].legend(fontsize=9)
axes[2].grid(True, linestyle=':', alpha=0.7)
axes[2].set_xticks(processes)
axes[2].set_ylim(0, 1.1)

plt.tight_layout()
plt.savefig('performance_plots.png', dpi=300, bbox_inches='tight')
plt.show()