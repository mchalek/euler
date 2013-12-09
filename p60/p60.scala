import collection.mutable
import collection.immutable.ListSet
import annotation.tailrec

@tailrec def toListSet[A](seq: Seq[A], accum: ListSet[A] = ListSet.empty[A]): ListSet[A] = {
  if(seq.isEmpty)
    accum
  else
    toListSet(seq.init, accum + seq.last)
}

def primes(N: Int): ListSet[Int] = {
  val composites = Array.fill(N+1)(false)

  val result: Seq[Int] = 
    for{ 
      i <- Range(2, N)
      if !composites(i)
    } yield {
      Range(2*i, N, i).foreach(composites(_) = true)
      i
    }

  toListSet(result)
}

def concatenations(p: Int)(implicit primes: ListSet[Int]): Seq[(Int, Int)] = {
  def toInt(digits: String) = digits.mkString("").toInt

  def getPairs(digits: String) = 
    for {
      i <- 1 until digits.length
      (a,b) = digits.splitAt(i) if primes((a + b).toInt)
      pp = toInt(a) if primes(pp)
      qq = toInt(b) if primes(qq)
    } yield (pp, qq)

  val leftToRight = getPairs(p.toString)
  val rightToLeft = getPairs(p.toString.reverse)

  leftToRight ++ rightToLeft
}

def allConcatenations(N: Int)(implicit primes: ListSet[Int]) = {
  primes.takeWhile(_ < N).flatMap(concatenations(_))
}

def isPrime(k: Int)(implicit p: ListSet[Int]) = {
  if(k < p.max) { 
    p(k)
  } else if(k < p.max * p.max) {
    p.forall(k % _ != 0)
  } else sys.error(s"can't check: $k")

}

def check(chain: Seq[Int])(implicit p: ListSet[Int]) = 
  chain.combinations(2).forall { 
    case List(a,b) => 
      isPrime((a.toString + b.toString).toInt) && 
      isPrime((b.toString + a.toString).toInt)
  }


def chains(implicit maxLen: Int, symm: Map[Int, Seq[Int]], p: ListSet[Int]): Set[Seq[Int]] = {
  def chain(current: Seq[Int]): Seq[Seq[Int]] = {
    if(current.length == maxLen)
      return Seq(current)

    // filter out values already in current to avoid cycles
    for { 
      c <- symm.getOrElse(current.head, Seq())

      newCurrent = c +: current if check(newCurrent)

      ch <- chain(c +: current)
    } yield ch
  }

  symm.keys.map(p => chain(Seq(p))).flatten.toSet
}

def lowestSum(k: Int)(implicit symm: Map[Int, Seq[Int]], p: ListSet[Int]): Int = {

  val all = chains(k/2+1, symm, p)
  val left = all.groupBy(ch => ch.last).mapValues(aSeq => aSeq.map(_.init))
  println(s"left size: ${left.size}")
  val right = 
    all.map { 
      case ch if(k % 2 == 0) => ch.reverse.tail
      case ch => ch.reverse
    }.groupBy(ch => ch.head).mapValues(chSeq => chSeq.map(_.tail))

  println(s"right size: ${right.size}")

  var result = Int.MaxValue
  var lowestSeq = Seq.empty[Int]
  for {
    (mid, rightChains) <- right
    leftChains <- left.get(mid).toSeq
    rc <- rightChains
    lc <- leftChains if lc.intersect(rc).isEmpty
    chain = lc ++ (mid +: rc)
    if check(chain)
    chainSum = chain.sum
    if chainSum < result
  } { result = chainSum; lowestSeq = lc ++ (mid +: rc) }

  println("lowest seq: " + lowestSeq.mkString(","))

  result
}

def solve(k: Int, maxP: Int, maxC: Int) {
  implicit val p = primes(maxP)
  val all = allConcatenations(maxC)
  implicit val symmetric = all.filter { case (p, q) => all((q,p)) }.groupBy(a => a._1).mapValues(_.unzip._2.toSeq)

  lowestSum(k)
}

solve(5, 2000000, 400000)

