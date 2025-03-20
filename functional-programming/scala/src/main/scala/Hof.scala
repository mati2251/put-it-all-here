package basics

def hof(): Unit = 
  val x = List(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
  val evenSum = calculate(x, isEven)
  val oddSum = calculate2(x) {isOdd}
  val allSum = calculate2(x) {x => true}
  println("HIGHER ORDER FUNCTIONS")
  println(s"Sum of even numbers: $evenSum")
  println(s"Sum of odd numbers: $oddSum")
  println(s"Sum of all numbers: $allSum")

  println("LOAN DESIGN PATTERN")
  readFile("src/main/resources/lorem.txt") { file =>
    val buffer = new Array[Char](file.read())
    file.read(buffer)
    println(buffer.mkString)
  }

def calculate(x: List[Int], f: (Int) => Boolean): Int =
  x.filter(f).sum

def calculate2(x: List[Int]) (f: Int => Boolean): Int =
  x.filter(f).sum
def isEven(x: Int): Boolean = x % 2 == 0

def isOdd(x: Int): Boolean = x % 2 != 0

def readFile[T] (fileName: String) (f: java.io.FileReader => T): T =
  val file = new java.io.File(fileName) 
  val reader = new java.io.FileReader(file)
  try
    f(reader)
  finally
    reader.close()
