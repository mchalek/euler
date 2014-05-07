import scala.collection.breakOut
import scala.collection.immutable._

case class Fraction(num: Long, den: Long) extends Ordered[Fraction] {
  /*
  override def equals(that: Any) = {
    that match {
      case Fraction(n2, d2) => n2 * den == d2 * num
      case _ => false
    }
  }*/

  private def partialReduce = {
    var newNum = num
    var newDen = den

    //val primes = Seq(2,3,5,7,11,13,17,19,23,29,31,37)
    val primes = Seq(2,3,5,7,11)

    primes.foreach { p =>
      while(newNum % p == 0 && newDen % p == 0) {
        newNum /= p
        newDen /= p
      }
    }

    Fraction(newNum, newDen)
  }

  def compare(that: Fraction): Int = {
    val a = num * that.den
    val b = den * that.num

    if(a == b) 0 else if(a > b) 1 else -1
  }

  def +(that: Fraction) = {
    val newNum = num * that.den + den * that.num
    val newDen = den * that.den 
    if(newNum % newDen == 0)
      Fraction(newNum / newDen, 1).partialReduce
    else if (newDen % newNum == 0)
      Fraction(1, newDen / newNum).partialReduce
    else
      Fraction(newNum, newDen).partialReduce
  }

  def inv = Fraction(den, num)

  override def toString = if(den == 1) num.toString else s"$num/$den"
}

object P155 {
  def series(a: Fraction, b: Fraction): Fraction = a + b

  def parallel(a: Fraction, b: Fraction): Fraction = (a.inv + b.inv).inv

  def iterate(
    n: Long,
    k: Long = 1,
    counts: Map[Long, TreeSet[Fraction]] = Map(1l -> TreeSet(Fraction(60, 1)))): TreeSet[Fraction] = {

    println(s"current depth is $k")

    if(n == k)
      return TreeSet(Fraction(60, 1))

    val current: TreeSet[Fraction] = counts.flatMap { case (i, values) =>
      val complementary = counts.getOrElse(k - i + 1, Seq.empty[Fraction]).toSeq

      for {
        v <- values.toSeq
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
println(Seq(18, P155.iterate(18).size).mkString(" -> "))
