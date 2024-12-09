operations = ["*", "+", "||"]

def could_equal(values, index, total, running_total):
    if index == len(values):
        return total == running_total
    
    # print("accessing with index " + str(index))
    val = values[index]
    for operation in operations:
        new_running_total = 0
        if operation == "||":
             new_running_total = int(str(running_total) + val)
        else:
            new_running_total = eval(str(running_total) + operation + val)
        #  print(new_running_total)
        next = could_equal(values, index+1, total, new_running_total)
        if next:
              return next
    
    return False


filename = "input.txt"
summed_possible_values = 0
with open(filename) as file:
    loop_counter = 1
    for full_line in file:
        line = full_line.rstrip()
        parts = line.split(":")

        result = int(parts[0])
        values = parts[1].strip().split(" ")

        first_val = int(values.pop(0))
        res = could_equal(values, 0, result, first_val)
        if res:
            print("Was possible")
            summed_possible_values += result
        
        print("Completed line: ", loop_counter)
        loop_counter += 1
        
                
    print(summed_possible_values)
