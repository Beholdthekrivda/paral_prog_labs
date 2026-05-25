import matplotlib.pyplot as plt
import numpy as np

# Данные из таблиц
processes = np.array([1, 2, 4, 8, 12, 16, 20, 24, 32])

# i-k-j порядок (первая таблица)
time_ikj = np.array([8.80023, 4.40715, 2.28878, 1.14195, 0.960981, 
                     0.918247, 0.880148, 0.876501, 0.876211])
speedup_ikj = np.array([1, 1.99680746060379, 3.84494359440401, 7.70631814002365, 
                        9.15754838024894, 9.58372856105166, 9.998579784309, 
                        10.0401824983657, 10.04350550267])
efficiency_ikj = np.array([1, 0.998403730301896, 0.961235898601001, 0.963289767502956, 
                           0.763129031687411, 0.598983035065729, 0.49992898921545, 
                           0.418340937431903, 0.313859546958438])

# k-i-j порядок (вторая таблица)
time_kij = np.array([8.81932, 4.43263, 2.3077, 1.15852, 1.01453, 
                     0.95925, 0.883853, 1.86397, 3.02004])
speedup_kij = np.array([1, 1.98963594976346, 3.82169259435802, 7.61257466422677, 
                        8.69301055661242, 9.19397445921293, 9.97826561656746, 
                        4.73147100006974, 2.9202659567423])
efficiency_kij = np.array([1, 0.994817974881729, 0.955423148589505, 0.951571833028347, 
                           0.724417546384368, 0.574623403700808, 0.498913280828373, 
                           0.197144625002906, 0.0912583111481967])

# Настройка для отображения кириллицы
plt.rcParams['font.sans-serif'] = ['DejaVu Sans', 'Arial', 'Liberation Sans']
plt.rcParams['axes.unicode_minus'] = False

# Создание фигуры с 3 графиками
fig, axes = plt.subplots(1, 3, figsize=(18, 6))

# --- График 1: Время выполнения ---
# Сначала i-k-j (красный), потом k-i-j (синий)
axes[0].plot(processes, time_ikj, marker='s', color='red', label='i-k-j', linewidth=2, markersize=6)
axes[0].plot(processes, time_kij, marker='o', color='blue', label='k-i-j', linewidth=2, markersize=6)

axes[0].set_title('Время выполнения', fontsize=14, fontweight='bold')
axes[0].set_xlabel('Количество процессов (p)', fontsize=12)
axes[0].set_ylabel('Время (сек)', fontsize=12)
axes[0].legend(fontsize=10)
axes[0].grid(True, linestyle=':', alpha=0.7)
axes[0].set_xticks(processes)

# --- График 2: Ускорение ---
# Сначала i-k-j (красный), потом k-i-j (синий)
axes[1].plot(processes, speedup_ikj, marker='s', color='red', label='i-k-j (реальное)', linewidth=2, markersize=6)
axes[1].plot(processes, speedup_kij, marker='o', color='blue', label='k-i-j (реальное)', linewidth=2, markersize=6)
axes[1].plot(processes, processes, linestyle='--', color='gray', label='Идеальное (S=p)', linewidth=1.5)

axes[1].set_title('Ускорение (Speedup)', fontsize=14, fontweight='bold')
axes[1].set_xlabel('Количество процессов (p)', fontsize=12)
axes[1].set_ylabel('S_p = T_1/T_p', fontsize=12)
axes[1].legend(fontsize=9)
axes[1].grid(True, linestyle=':', alpha=0.7)
axes[1].set_xticks(processes)

# --- График 3: Эффективность ---
# Сначала i-k-j (красный), потом k-i-j (синий)
axes[2].plot(processes, efficiency_ikj, marker='s', color='red', label='i-k-j (реальная)', linewidth=2, markersize=6)
axes[2].plot(processes, efficiency_kij, marker='o', color='blue', label='k-i-j (реальная)', linewidth=2, markersize=6)
axes[2].axhline(y=1, linestyle='--', color='gray', label='Идеальная (E=1)', linewidth=1.5)

axes[2].set_title('Эффективность (Efficiency)', fontsize=14, fontweight='bold')
axes[2].set_xlabel('Количество процессов (p)', fontsize=12)
axes[2].set_ylabel('E_p = S_p/p', fontsize=12)
axes[2].legend(fontsize=9)
axes[2].grid(True, linestyle=':', alpha=0.7)
axes[2].set_xticks(processes)
axes[2].set_ylim(0, 1.1)

plt.tight_layout()
plt.savefig('comparison_plots_ikj_kij.png', dpi=300, bbox_inches='tight')
plt.show()