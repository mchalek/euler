import scala.annotation.tailrec

val N = 12000
val primes = {
  val composites = collection.mutable.Set.empty[Int]

  for { 
    p <- Range(2, N) if !composites(p)
  } yield {
    composites ++= Range(2*p, N, p).toSet
    p
  }
}

@tailrec def factors(c: Int, pr: Seq[Int], acc: Map[Int, Int] = Map.empty): Map[Int, Int] = {
  @tailrec def countFactors(resid: Int, p: Int, count: Int = 0): (Int, Int) = {
    if(resid % p != 0)
      return (resid, count)

    countFactors(resid / p, p, count + 1)
  }

  if(pr.isEmpty)
    return acc

  val p = pr.head

  if(p*p > c) {
    if(pr.contains(c))
      return acc ++ Map(c -> 1)
    else
      return acc
  }

  val (residual, count) = countFactors(c, p)

  val newAcc = if(count > 0) acc ++ Map(p -> count) else acc
  
  factors(residual, pr.tail, newAcc)
}

def isTerminating(n: Int, d: Int) = {
  val nfactors = factors(n, primes)
  val dfactors = factors(d, primes)

  val allPrimes = nfactors.keySet ++ dfactors.keySet
  val reducedDenominator = allPrimes.map { p => 
    p -> (nfactors.getOrElse(p, 0) - dfactors.getOrElse(p, 0)) }.filter { case (_, c) => c < 0 }

  reducedDenominator.forall { case (p, _) => p == 2 || p == 5 }
}

def getMaxK(N: Int) = {
  def z(k: Double) =
    k*(math.log(N.toDouble) - math.log(k))

  val e = math.exp(1)
  val maxReal = N.toDouble / e
  val k1 = math.ceil(maxReal)
  val z1 = z(k1)
  val k2 = math.floor(maxReal)
  val z2 = z(k2)

  if(z1 > z2)
    k1.toInt
  else
    k2.toInt
}

def results(maxN: Int) = 
  for {
    n <- (5 to maxN)
    k = getMaxK(n)
    term = isTerminating(n, k)
  } yield { 
    if(term) -n else n
  }

println(s"for n from 5 to 100: ${results(100).sum}")
println(s"for n from 5 to 100: ${results(10000).sum}")

