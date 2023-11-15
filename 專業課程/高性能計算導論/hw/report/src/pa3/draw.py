import matplotlib.pyplot as plt

dataset = []
with open('1.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        res = [item for item in line.replace('\n', '').split(' ') if len(item) > 0]
        dataset.append((res[0], float(res[3])))
        
fig, ax = plt.subplots(figsize=(10, 6))

# labels = ['precision', 'recall', 'f1-score']
# x = range(len(labels))

bar_width = 0.2
opacity = 0.8

for i, (name, scores) in enumerate(dataset):
    ax.bar(name, scores, bar_width, alpha=opacity, label=name)

ax.hlines(y=0, linestyle='--')
ax.set_xlabel('Metrics')
ax.set_ylabel('Scores')
ax.set_title('Performance Comparison')
# ax.set_xticks([j + 2*bar_width for j in x])
# ax.set_xticklabels(labels)


plt.tight_layout()
plt.show()