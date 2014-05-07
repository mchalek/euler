import scala.collection.breakOut

case class Fraction(num: Long, den: Long) {
  override def equals(that: Any) = {
    that match {
      case Fraction(n2, d2) => n2 * den == d2 * num
      case _ => false
    }
  }

  override def hashCode = math.round(1e3*num.toDouble / den).hashCode

  def +(that: Fraction) = {
    val newNum = num * that.den + den * that.num
    val newDen = den * that.den 
    if(newNum % newDen == 0)
      Fraction(newNum / newDen, 1)
    else
      Fraction(newNum, newDen)
  }

  def inv = Fraction(den, num)
}

object P155 {
  def series(a: Fraction, b: Fraction): Fraction = a + b

  def parallel(a: Fraction, b: Fraction): Fraction = (a.inv + b.inv).inv

  def iterate(
    n: Long,
    k: Long = 1,
    counts: Map[Long, Set[Fraction]] = Map(1l -> Set(Fraction(60, 1)))): Set[Fraction] = {

    println(s"current depth is $k")

    if(n == k)
      return Set(Fraction(60, 1))

    val current: Set[Fraction] = counts.flatMap { case (i, values) =>
      val complementary = counts.getOrElse(k - i + 1, Set.empty[Fraction])

      for {
        v <- values
        c <- complementary
        newValue <- Seq(series(c, v), parallel(c, v))
      } yield newValue
    }(breakOut)

    current ++ iterate(n, k+1, counts + ((k+1) -> current))
  }
}

println(Seq(1, P155.iterate(1).size).mkString(" -> "))
println(Seq(2, P155.iterate(2).size).mkString(" -> "))
println(Seq(3, P155.iterate(3).size).mkString(" -> "))
println(Seq(4, P155.iterate(4).size).mkString(" -> "))
println(Seq(5, P155.iterate(5).size).mkString(" -> "))
//println(Seq(6, P155.iterate(6).size).mkString(" -> "))
//println(Seq(7, P155.iterate(7).size).mkString(" -> "))
//println(Seq(8, P155.iterate(8).size).mkString(" -> "))
//println(Seq(9, P155.iterate(9).size).mkString(" -> "))
//println(Seq(10, P155.iterate(10).size).mkString(" -> "))
//println(Seq(11, P155.iterate(11).size).mkString(" -> "))
//println(Seq(12, P155.iterate(12).size).mkString(" -> "))
//println(Seq(13, P155.iterate(13).size).mkString(" -> "))
//println(Seq(14, P155.iterate(14).size).mkString(" -> "))
//println(Seq(15, P155.iterate(15).size).mkString(" -> "))
//println(Seq(16, P155.iterate(16).size).mkString(" -> "))
//println(Seq(17, P155.iterate(17).size).mkString(" -> "))
println(Seq(18, P155.iterate(18).size).mkString(" -> "))
