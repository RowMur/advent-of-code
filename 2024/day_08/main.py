input = "input.txt"
grid_size = 0

nodes = {}
with open(input) as file:
    line_counter = 0
    for full_line in file:
        line = full_line.rstrip()
        grid_size = len(line)
        for i, c in enumerate(line):
            if c == ".":
                continue

            if not c in nodes:
                nodes[c] = []
            
            nodes[c].append((i, line_counter))
        
        line_counter += 1
    
    print(nodes)

antinodes = set()
for node_type in nodes:
    for i in nodes[node_type]:
        for j in nodes[node_type]:
            if i == j:
                continue

            dx = i[0] - j[0]
            dy = i[1] - j[1]

            x = i[0]
            y = i[1]
            while True:
                x -= dx
                y -= dy
                
                if not (0 <= x < grid_size and 0 <= y < grid_size):
                    break

                antinode = (x, y)
                antinodes.add(antinode)

print(antinodes)
print(len(antinodes))