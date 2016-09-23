val nB = 10
val nW = 5

def count = {
  val results = collection.mutable.Set.empty[Seq[(Int, Int)]]

  def build(current: List[(Int, Int)] = List.empty[(Int, Int)],
            rb: Int = nB, rw: Int = nW): Unit = {
    //println(s"current is: $current; rb: $rb, rw: $rw")
    if(rb == 0 && rw == 0) {
      results += current.sortBy { case (a, b) => a*1000 + b }
      //results += current
      //println("inserting!")
      return
    }

    val minB = 0 // math.min(rb, current.headOption.map(_._1).getOrElse(0))
    val maxB = rb
    val maxW = rw // math.min(rw, current.headOption.map(_._2).getOrElse(nW))
    val minW = 0
    //println(s"B: $minB to $maxB; W: $minW to $maxW")
    for { 
      nb <- (minB to maxB)
      nw <- (minW to maxW) if nb > 0 || nw > 0
      elem = (nb, nw)
    } {
      //if(current.isEmpty)
        //println("level 0")
      //println(s"nb is $nb, nw is $nw")
      build(elem :: current, rb - nb, rw - nw)
    }
  }

  build()
  //println(results)
  results.size
}

println(s"result: $count")

