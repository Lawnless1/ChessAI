out = "{"
for i in range(6, 8):
    for j in range(8):
        out = out + "{make_pair(" + str(i) + ", " + str(j) + "), 'p'}, "
out = out + "}"
print(out)
