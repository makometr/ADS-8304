import random
import subprocess
import numpy as np
import matplotlib.pyplot as plt

alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z']

static_points_x = []
dinamic_points_x = []
points_y = []

for k in range(1, 5):  # range (1, 4)
    for i in range(8):  # range(10)
        string = []
        j = 0
        for j in range(pow(10, k)):  # range(100 * k)
            string.append(random.choice(alphabet))
        string = ''.join(string)
        with open("Tests/input.txt", "w+") as input_data:
            input_data.write(string)
        subprocess.call(['cmake-build-debug/Course_Work.exe', 'Tests/input.txt'])
        with open("dinamic_file.txt", 'r') as dinamic_dot_x:
            dinamic_dot_x = int(dinamic_dot_x.readline())
        with open("static_file.txt", 'r') as static_dot_x:
            static_dot_x = int(static_dot_x.readline())
        static_points_x.append(static_dot_x)
        dinamic_points_x.append(dinamic_dot_x)
        points_y.append(j)

import matplotlib.pyplot as plt

fig, axs = plt.subplots(1, 2, figsize=(10, 5), sharey=True)
axs[0].scatter(static_points_x, points_y)
axs[1].scatter(dinamic_points_x, points_y)
plt.show()
