package basics

def iteration(): Unit = 
  val prices = List(210.0, 310.12, 510.45, 645.10)

  for (price <- prices){
    print(price + " ")
  }
  println

  prices.foreach { println } 

  prices foreach println

  prices.find { price => price > 500 }

  println(prices map { price => price * 0.1 })

  println( "Total is " + prices.reduce  { (price1, price2) => price1 + price2} )

  println( "Total is " + prices.sum )
