package basics

def collections: Unit =
  list
  vector
  map
  mutableMap
  lazyCollection

def list: Unit = 
  println("LIST")
  val prices = List(10, 20, 30, 40, 50)
  prices.foreach { price => println(price)}  
  println("The first price is " + prices(0))
  
  println("First price > 40 is " + prices.find { price => price > 40 })
  println("Prices above 40 " + prices.filter { price => price > 40})
  println("Any > 40 " + prices.exists {price => price > 40})
  println("All > 40 " + prices.forall {price => price > 40})

  val items = List("A", "B", "C", "D", "E")
  println(items.zip(prices))

  val newPrices = 5::prices
  println(newPrices)

def vector: Unit = 
  println("VECTOR")
  val prices = Vector(10, 20, 30, 40, 50)
  prices.foreach { price => println(price)}
  val newPrices = 5 +: prices
  println(newPrices)

def map: Unit = 
  println("MAP")
  val langs = Map("Java" -> 20, "Scala" -> 10, "Python" -> 30)
  langs.foreach { case (key, value) => println(key + " " + value)}
  println(langs + ("C++" -> 40))

def mutableMap: Unit = 
  val capitals = scala.collection.mutable.Map("New York" -> "Albany")
  println(capitals)
  capitals += ("California" -> "Sacramento")
  println(capitals)

def lazyCollection: Unit = 
  val numbers = (1 to 100).toList
  val squaresLazy = numbers.view.map { n => n * n }
  println(squaresLazy)
  println(squaresLazy.force)
