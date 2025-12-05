def subsecuencia_mayor(line, k=12):
    nums = [int(x) for x in line]

    n = len(nums)
    libre = n - k

    stack = []

    for num in nums:
        while libre > 0 and stack and stack[-1] < num:
            stack.pop()
            libre -= 1
        stack.append(num)
 
    return "".join(map(str, stack[:k]))

def main():
    resultado = 0

    with open('03_input.dat') as f:
        for line in f:
            line = line.strip()
            if not line: continue

            mejor = subsecuencia_mayor(line, 12)
            resultado += int(mejor)

        print(f"Resultado: {resultado}")

if __name__ == "__main__":
    main()
