import argparse
import random

import math

parser = argparse.ArgumentParser(description='Generates input samples.')
parser.add_argument('count', type=int, help='Count of samples')
parser.add_argument("-m", "--max_value", nargs='?', default=20000.0, type=float, action="store",
                    help="Max value in samples")

args = parser.parse_args()
N = args.count

max_value = args.max_value

bins_count = random.randint(15, 25)
# bins_count = 1
bins = []
for i in range(bins_count):
    bins.append((random.gauss(max_value, max_value/2),
                 1.0/random.gauss(N/100,N/1000) * (2 * math.pi),
                 round(random.gauss(0, (2 * math.pi)/3), 2)))

# print([1/(bin[1]/(2 * math.pi)) for bin in bins[:3]])
# print([bin[0]/max_value-1 for bin in bins[:3]])
cnt = int(2 ** math.ceil(math.log(N, 2)))
with open("input.txt", "w+") as f:
    for i in range(N):
        value = sum([bin[0] * (math.sin(i * bin[1] + bin[2])) for bin in bins])
        f.write("%f\n" % value)

    f.write("0.0\n"*(cnt-1-N))
    f.write("0.0")
