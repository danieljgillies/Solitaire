import numpy as np

#$ \prod_{j=0}^a (1 - \prod_{I=0}^{\lceil(\frac{a -j /b)\rceil}((a - j - c -i)/(a -j -i) ))$
def talon_prob(Ns, Ncps, m):
    Nc=Ns*Ncps

    prob_all=1
    for i in range(0, Nc -Ns):
        prob_round=1
        for j in range(0, int(np.ceil((Nc - i)/m))):
            prob_round=prob_round*((Nc -j - Ns -i)/(Nc -j -i))
        #print( int(np.ceil((Nc - i)/m)))
        #print(f"Round {i}: {1-prob_round}")
        prob_all=prob_all*(1 - prob_round)
    
    return prob_all


print(talon_prob(4, 13, 1))
print(talon_prob(4, 13, 2))
print(1/talon_prob(4, 13, 3))
print(talon_prob(4, 13, 4))


print(talon_prob(4, 5, 1))
print(talon_prob(4, 5, 2))
print(talon_prob(4, 5, 3))

print(talon_prob(1, 5, 1))
print(talon_prob(1, 5, 2))
print(talon_prob(1, 5, 3))


probs_with_m=[]
ms=[]
for i in range(1, 52):
    probs_with_m.append(talon_prob(4, 13, i))
    ms.append(i)

import matplotlib.pyplot as plt
plt.xlabel("m (number of cards drawn per round)")
plt.ylabel("Probability of winning (%)")
plt.title("Probability of winning vs m (4 suits, 13 cards each)")
plt.plot(ms, 100*np.array(probs_with_m))

plt.semilogy()
plt.savefig("talon_prob_vs_m.pdf")