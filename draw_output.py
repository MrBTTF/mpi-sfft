import argparse

import math
import matplotlib.pyplot as plt

samples = []

parser = argparse.ArgumentParser(description='Generates input samples.')
parser.add_argument("-r", "--sample_rate", nargs='?', default=22400, type=int, action="store",
                    help="Sample rate in kHz")

args = parser.parse_args()
sample_rate = args.sample_rate

with open("output.txt","r") as f:
    for line in f.readlines():
        samples.append(complex(line))

print(sample_rate)

amps = [math.log(abs(sample)) for sample in samples[:int(len(samples)/2)]]
freqs = [i*float(sample_rate)/(len(samples)/2) for i in range(int((len(samples)/2)))]

plt.plot(freqs,amps)
plt.xlabel('Frequency')
plt.ylabel('Amplitude')

plt.show()
