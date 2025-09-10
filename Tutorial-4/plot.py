import matplotlib.pyplot as plt

data = {}
with open("values.dat", "r") as f:
    for line in f:
        n, threads, t = line.split()
        n, threads, t = int(n), int(threads), float(t)
        if threads not in data:
            data[threads] = {"sizes": [], "times": []}
        data[threads]["sizes"].append(n)
        data[threads]["times"].append(t)

plt.figure(figsize=(8,6))
for threads, values in sorted(data.items()):
    plt.plot(values["sizes"], values["times"], marker='o', label=f"{threads} threads")

plt.xlabel("Matrix Size (n)")
plt.ylabel("Execution Time (s)")
plt.title("Matrix-Vector Multiplication Scaling")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
