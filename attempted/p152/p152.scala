import scala.collection.mutable

object P152 {
  val primesAndMaxPowers =
    Seq(
      2 -> 6,
      3 -> 4,
      5 -> 2,
      7 -> 2,
      11 -> 1,
      13 -> 1,
      17 -> 1,
      19 -> 1,
      23 -> 1,
      29 -> 1,
      31 -> 1,
      37 -> 1)

  private def buildExponents(maxExponents: Seq[Int]): Seq[List[Int]] = {
    val items = mutable.Buffer.empty[List[Int]]

    def build(maxes: List[Int], current: List[Int]) {
      if(maxes.isEmpty) {
        items += current
        return
      }

      val nextMax::remaining = maxes

      var e = 0
      while(e <= nextMax) {
        build(remaining, e :: current)
        e += 1
      }
    }

    build(maxExponents.reverse.toList, List())

    items.toSeq
  }

  def generateGCD = buildExponents(primesAndMaxPowers.unzip._2)

  val all1 = (1l << primesAndMaxPowers.length) - 1
  def pack(used: Seq[Int]) = {
    var result = 0l
    var index = 0
    used.foreach {
      case u if u > 0 => 
        result |= (1l << index)
        index += 1
      case _ =>
        index += 1
    }

    result.toLong
  }

  def unpack(used: Long) = {
    (0 until primesAndMaxPowers.length).map { ind =>
      ((used >> ind) & 1) == 1
    }
  }

  def countCoprime(gcd: Seq[Int]): Int = {
    //println(s"gcd exponents: ${gcd}")
    //println(s"primes used by gcd: ${unpack(pack(gcd))}")
    def buildResiduals(used: Long): Seq[(Long, List[Int])] = {
      val maxPowers = primesAndMaxPowers.unzip._2.zipWithIndex.map {
        case (exp, ind) if ((used >> ind) & 1l) == 0 => 
          exp
        case (exp, _) =>
          0
      }

      val residualsFactored = buildExponents(maxPowers)
      residualsFactored.map(rf => (used | pack(rf), rf))
    }

    import mutable.Queue

    val q = Queue.empty[(Long, Set[List[Int]])]

    q.enqueue((pack(gcd), Set()))
    
    var count = 0

    while(!q.isEmpty) {
      val (used, residuals) = q.dequeue

      val nextResiduals = buildResiduals(used)
      //println(s"got: ${residuals}, begets ${nextResiduals.length} new ones")
      nextResiduals.foreach {
        case (nextUsed, _) if nextUsed == all1 =>
        case (_, newResidual) if residuals.contains(newResidual) =>
        case (nextUsed, newResidual) =>
          q.enqueue((nextUsed, residuals + newResidual))
          count += 1
      }
    }

    count
  }
}

val gcds = P152.generateGCD
println(s"# GCDs: ${gcds.length}")

println(s"packed(gcd(20000)) == ${P152.pack(gcds(20000))}")

gcds.zipWithIndex.foreach { case (gcd, ind) =>
  println(s"count_coprime(gcd($ind)) == ${P152.countCoprime(gcd)}")
}
