import matplotlib.pyplot as plt
import numpy as np

# Данные из твоей таблицы
processes = np.array([1, 2, 4, 8, 12, 16, 20, 24, 32])
speedup = np.array([1, 1.99734683148101, 3.96277402186596, 7.88686359565588,
                    8.68802850608945, 13.1417377943318, 8.05871340586591,
                    9.4289865249864, 11.843117533874])
efficiency = np.array([1, 0.998673415740503, 0.99069350546649, 0.985857949456985,
                       0.724002375507455, 0.821358612145736, 0.402935670293296,
                       0.392874527187444, 0.370097417308564])

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