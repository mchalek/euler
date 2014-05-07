import scala.collection.breakOut

object P155 {
  val mergeFns = Seq(
    (a: Double, b: Double) => a + b,
    (a: Double, b: Double) => 1.0 / (1.0 / a + 1.0 / b))
     
  def iterate(n: Int, k: Int = 1, counts: Map[Int, Set[Double]] = Map(1 -> Set(60.0))): Set[Double] = {
    if(n == k)
      return Set(60.0)

    val current: Set[Double] = counts.flatMap { case (i, values) =>
      val complementary = counts.getOrElse(k - i + 1, Set.empty[Double])

      for {
        v <- values
        c <- complementary
        f <- mergeFns
      } yield f(c,v)
    }(breakOut)

    current ++ iterate(n, k+1, counts + ((k+1) -> current))
  }
}

println(P155.iterate(1).size)
println(P155.iterate(2).size)
println(P155.iterate(3).size)
println(P155.iterate(4).size)
println(P155.iterate(5).size)
