import random
def generateSumTest(a, b):  
  return ("sum {} {} {}\n".format(a, b, a + b))

def generateDiffTest(a, b):  
  return ("diff {} {} {}\n".format(a, b, a - b))
def generateDiffTests(k, t, c):
  result = []
  result.append(generateDiffTest(0, 0))
  result.append(generateDiffTest(-1, 0))
  result.append(generateDiffTest(0, -1))
  result.append(generateDiffTest(1, -1))
  result.append(generateDiffTest(-1, 1))

  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    b = random.randint(-(10**t), 10**t)
    result.append(generateDiffTest(a, b))
  return result

def generateSumTests(k, t, c):
  result = []
  result.append(generateSumTest(0, 0))
  result.append(generateSumTest(-1, 0))
  result.append(generateSumTest(0, -1))
  result.append(generateSumTest(1, -1))
  result.append(generateSumTest(-1, 1))

  result.append(generateSumTest(10000, -1000000))
  result.append(generateSumTest(10000, 1232131232))
  result.append(generateSumTest(-123231, 1232131232))
  result.append(generateSumTest(-123231, -1232131232))
  result.append(generateSumTest(-352342141130909498301948, -7983941324093497091))
  result.append(generateSumTest(-352342141130909498301948, 7983941324093497091))
  result.append(generateSumTest(352342141130909498301948, -7983941324093497091))
  result.append(generateSumTest(352342141130909498301948, 7983941324093497091))

  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    b = random.randint(-(10**t), 10**t)
    result.append(generateSumTest(a, b))
  return result
def generateInitTest(a):
  return ("init {} {}\n".format(a, a))

def generateInitTests(k, c):
  result = []
  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    result.append(generateInitTest(a))
  return result

def generateCopyTest(a):
  return ("copy {} {}\n".format(a, a))

def generateCopyTests(k, c):
  result = []
  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    result.append(generateCopyTest(a))
  return result  

def generateCompareTest(a, b):
  r1 = ("less {} {} {}\n").format(a, b, int(a < b))
  r2 = ("great {} {} {}\n").format(a, b, int(a > b))
  r3 = ("notless {} {} {}\n").format(a, b, int(a >= b))
  r4 = ("notgreat {} {} {}\n").format(a, b, int(a <= b))
  r5 = ("equal {} {} {}\n").format(a, b, int(a == b))
  return [r1, r2, r3, r4, r5]

def generateCompareTests(k, t, c):
  result = []
  result += generateCompareTest(0, 0)
  result += generateCompareTest(0, 1)
  result += generateCompareTest(1, 0)
  result += generateCompareTest(1, 1)
  result += generateCompareTest(0, 0)
  result += generateCompareTest(0, -1)
  result += generateCompareTest(-1, 0)
  result += generateCompareTest(-1, -1)
  result += generateCompareTest(1, -1)
  result += generateCompareTest(-1, 1)
  
  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    b = random.randint(-(10**t), 10**t)
    result += generateCompareTest(a, b)
    result += generateCompareTest(a, a)
  return result

def generateIncDecTest(a):
  r1 = ("inc {} {}\n").format(a, a + 1)
  r2 = ("dec {} {}\n").format(a, a - 1)
  return [r1, r2]
  
def generateIncDecTests(k, c):
  result = []
  result += generateIncDecTest(0)
  result += generateIncDecTest(1)
  result += generateIncDecTest(-1)
  result += generateIncDecTest(2)
  result += generateIncDecTest(-1)
  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    result += generateIncDecTest(a)
  return result

def generateMulDivTest(a, b):
  result = []
  result.append("mul {} {} {}\n".format(a, b, a * b))
  if b != 0:
    result.append("div {} {} {}\n".format(a, b, a // b))
  return result

def generateMulDivTests(k, t, c):
  result = []
  result += generateMulDivTest(1, 0)
  result += generateMulDivTest(1, 1)
  result += generateMulDivTest(0, 1)
  result += generateMulDivTest(0, 0)
  result += generateMulDivTest(0, -1)
  result += generateMulDivTest(-1, -1)
  result += generateMulDivTest(-1, 1)
  result += generateMulDivTest(1, -1)

  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    b = random.randint(-(10**t), 10**t)
    result += generateMulDivTest(a, b)
  return result

def generateModTest(a, b):
  result = []
  if b != 0:
    result.append("mod {} {} {}\n".format(a, b, a % b))
  return result

def generateModTests(k, t, c):
  result = []
  for i in range(c):
    a = random.randint(-(10**k), 10**k)
    b = random.randint(-(10**t), 10**t)
    result += generateModTest(a, b)
  return result

def generateSpecTests():
  result = []
  a = int("100000000001000001000001000001000010000001000001000001000001000000000000001000000000000000000000001000000000000001000")
  for i in range(1000):
    b = random.randint(-(10**5), 10**5)
    result += generateMulDivTest(a, b)
    result += generateModTest(a, b)
    
  return result

def generateTests():
  result = []
  result += generateSpecTests()

  result += generateSumTests(50, 50, 10000)
  result += generateDiffTests(50, 50, 10000)
  result += generateInitTests(50, 1000)
  result += generateCopyTests(20, 10000)
  result += generateCompareTests(40, 40, 10000)
  result += generateIncDecTests(5, 1000)

  result += generateMulDivTests(5, 5, 10000)
  result += generateMulDivTests(100, 7, 10000)
  result += generateMulDivTests(50, 10, 10000)
  result += generateMulDivTests(20, 20, 10000)
  
  result += generateModTests(2, 2, 10000)
  result += generateModTests(30, 20, 10000)
  result += generateModTests(30, 3, 10000)
  return result

outstream = open("test.txt", "w")
result = generateTests()


outstream.write(str(len(result)) + "\n" + "".join(result))


