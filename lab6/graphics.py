import matplotlib.pyplot as plt
import numpy as np

# Данные из твоей таблицы
processes = np.array([1, 2, 4, 8, 12, 16, 20, 24, 32])
speedup = np.array([1, 2.00669529793402, 3.86915572271632, 5.94117037060672,
                    8.92629901064856, 10.784328489572, 6.51633026238659,
                    8.69059468037316, 1.0234622239506])
efficiency = np.array([1, 1.00334764896701, 0.967288930679079, 0.74264629632584,
                       0.74385825088738, 0.674020530598823, 0.325816513119329,
                       0.362108111682215, 0.0319831944984561])

# Настройка шрифта для корректного отображения кириллицы
plt.rcParams['font.sans-serif'] = ['DejaVu Sans', 'Arial']

# Создание фигуры с двумя графиками
fig, axes = plt.subplots(1, 2, figsize=(14, 6))

# --- График 1: Ускорение (Speedup) ---
axes[0].plot(processes, speedup, marker='o', color='blue', label='Реальное ускорение', linewidth=2)
axes[0].plot(processes, processes, linestyle='--', color='gray', label='Идеальное линейное ускорение (S=p)', linewidth=1)

axes[0].set_title('Ускорение (Speedup)', fontsize=14, fontweight='bold')
axes[0].set_xlabel('Количество процессов (p)', fontsize=12)
axes[0].set_ylabel('Ускорение (S_p)', fontsize=12)
axes[0].legend()
axes[0].grid(True, linestyle=':', alpha=0.7)
axes[0].set_xticks(processes)

# --- График 2: Эффективность (Efficiency) ---
axes[1].plot(processes, efficiency, marker='o', color='red', label='Реальная эффективность', linewidth=2)
axes[1].plot([1, 32], [1, 1], linestyle='--', color='gray', label='Идеальная эффективность (E=1)', linewidth=1)

axes[1].set_title('Эффективность (Efficiency)', fontsize=14, fontweight='bold')
axes[1].set_xlabel('Количество процессов (p)', fontsize=12)
axes[1].set_ylabel('Эффективность (E_p)', fontsize=12)
axes[1].legend()
axes[1].grid(True, linestyle=':', alpha=0.7)
axes[1].set_xticks(processes)
axes[1].set_ylim(0, 1.1)  # Ограничение оси Y для наглядности (от 0 до 1.1)

plt.tight_layout()
plt.show()