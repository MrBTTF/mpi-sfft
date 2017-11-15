import argparse

import math
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Generates input samples.')
parser.add_argument("-r", "--sample_rate", nargs='?', default=22400, type=int, action="store",
                    help="Sample rate in kHz")
parser.add_argument("-c", "--count", nargs='?', default=20000, type=int, action="store",
                    help="Samples count")

args = parser.parse_args()
sample_rate = args.sample_rate
samples_count = args.count

print(sample_rate)

raw_samples = []
with open("input.txt", "r") as f:
    for line in f.readlines():
        raw_samples.append(float(line))

plt.figure(1)
plt.plot([i for i in range(samples_count)], raw_samples[:samples_count])
plt.xlabel('Time')
plt.ylabel('Amplitude')



samples = []
with open("output.txt", "r") as f:
    for line in f.readlines():
        samples.append(complex(line))

amps = [math.log10(abs(sample)) for sample in samples[:int(len(samples) / 2)]]
freqs = [i * float(sample_rate) / (len(samples) / 2) for i in range(int((len(samples) / 2)))]

plt.figure(2)
plt.plot(freqs, amps)
plt.xlabel('Frequency')
plt.ylabel('Amplitude')

plt.show()
