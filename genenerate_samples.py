import argparse
import random
import matplotlib.pyplot as plt

import math

parser = argparse.ArgumentParser(description='Generates input samples.')
parser.add_argument('count', type=int, help='Count of samples')
parser.add_argument("-m", "--max_value", nargs='?', default=20000.0, type=float, action="store",
                    help="Max value in samples")
parser.add_argument("-p", "--plot", action="store_true",
                    help="Show plot")

args = parser.parse_args()
N = args.count

max_value = args.max_value
show_plot = args.plot

samples = []

bins_count = random.randint(1, float(N) / 20)
print(bins_count)


bins = []
for i in range(bins_count):
    bins.append((random.uniform(max_value / 10, max_value),
                 random.gauss(N*5,0.5)/ (2 * math.pi),
                 random.gauss(0, 0.5)))

with open("input.txt", "w+") as f:
    for i in range(2 ** math.ceil(math.log(N, 2))):
        if i > N:
            f.write("%f" % 0)
            continue

        value = 0
        for bin in bins:
            value += bin[0]*(math.sin(i*bin[1]+bin[2])+1)

        # value = random.gauss(max_value/2, 0.9)*(math.sin(float(i)/(N/10)+random.uniform(0,N/100))+1)
        # value = random.uniform(0,max_value/100)*(math.sin(i/(N/10)+random.uniform(0,N/100.0))+1)
        # value = max_value*(math.sin(float(i)/N*10)+1)

        # if value < 0:
        #     value = 0
        # elif value > max_value:
        #     value = max_value

        samples.append(value)
        f.write("%f" % value)

        if i != N - 1:
            f.write("\n")

if show_plot:
    plt.plot([i for i in range(len(samples))], samples)
    plt.xlabel('Time')
    plt.ylabel('Amplitude')
    plt.show()

