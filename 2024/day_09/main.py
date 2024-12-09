input = "input.txt"

with open(input) as file:
    disk_map = file.readline().rstrip()

blocks = []
expected_length = 0
for i, digit in enumerate(disk_map):
    intDigit = int(digit)
    if intDigit == 0:
        continue

    if i % 2 == 1:
        blocks.append((-1, intDigit))
        continue

    blocks.append((int(i/2), intDigit))

for i, block in enumerate(blocks):
    print("Looping through blocks: ", i)
    if block[0] != -1:
        continue
    
    for j, later_block in enumerate(reversed(blocks)):
        j_in_regular_list = len(blocks) - j - 1
        if not i < j_in_regular_list:
            continue

        if later_block[0] == -1:
            continue
            
        if block[1] < later_block[1]:
            continue


        # print(blocks)
        remaining_space = block[1] - later_block[1]
        blocks[i] = blocks[j_in_regular_list]
        blocks[j_in_regular_list] = (-1, later_block[1])
        if remaining_space > 0:
            blocks.insert(i+1, (-1, remaining_space))
        
        break

flattened_blocks = []
for block in blocks:
    for _ in range(block[1]):
        flattened_blocks.append(block[0])

# print(flattened_blocks)

checksum = 0
for i, block in enumerate(flattened_blocks):
    if block == -1:
        continue

    checksum += i * block

# print(blocks)
print(checksum)