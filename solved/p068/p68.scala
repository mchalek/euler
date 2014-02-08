val valid = 1 to 10

def compute(
  items: Seq[Int] = Seq.empty,
  remaining: Seq[Int] = valid): Seq[Seq[Int]] = {
  val available =
    if(items.nonEmpty && items.length < 5)
      remaining.filter(x => x >= items.head)
    else
      remaining

  if(items.length == 6) { 
    val Seq(a, d, f, h, j, c) = items
    val i = a + c - j
    val e = h + i - f
    val b = d + e - a
    val g = a + b + c - e - f

    val derived = Set(i, e, b, g)
    val result = 
      if(derived.forall(available.contains) && derived.size == 4)
        Seq(a,b,c, d,c,e, f,e,g, h,g,i, j,i,b)
      else
        Seq.empty
    
    return Seq(result)
  }

  for { 
    a <- available
    sol <- compute(items :+ a, remaining.filterNot(_ == a)) if sol.nonEmpty
  } yield sol
}

val results = compute()

results.foreach { values =>
  //val string = values.grouped(3).map(_.mkString(",")).mkString(";")
  val string = values.mkString("")
  val total = values.take(3).sum
  println(s"$total  $string")
}

