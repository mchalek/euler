import collection.mutable
import collection.mutable.LinkedHashSet
import annotation.tailrec

def primes(N: Int): LinkedHashSet[Int] = {
  val composites = Array.fill(N+1)(false)

  val result: Seq[Int] = 
    for{ 
      i <- Range(2, N)
      if !composites(i)
    } yield {
      for(a <- Range(2*i, N, i)) { composites(a) = true }
      i
    }

  LinkedHashSet(result:_*)
}

def concat(a: Int, b: Int) = {
  var i = 1
  while(b / i != 0) {
    i *= 10
  }

  a*i + b
}

def concatenations(p: Int)(implicit primes: LinkedHashSet[Int]): Seq[(Int, Int)] = {
  @tailrec def getPairs(x: Int, div: Int = 10, accum: List[(Int, Int)] = List.empty): List[(Int, Int)] = {
    val a = x / div
    val b = x % div

    if(a == 0)
      return accum

    if(isPrime(a) && isPrime(b)) {
      getPairs(x, div*10, (a, b) +: accum)
    } else
      getPairs(x, div*10, accum)
  }

  val leftToRight = getPairs(p)
  val rightToLeft = getPairs(p.toString.reverse.toInt)

  leftToRight ++ rightToLeft
}

def allConcatenations(N: Int)(implicit primes: LinkedHashSet[Int]) = {
  primes.takeWhile(_ < N).flatMap(concatenations(_))
}

def isPrime(k: Int)(implicit p: LinkedHashSet[Int]) = {
  if(k < p.max) { 
    p(k)
  } else if(k < p.max.toLong * p.max) {
    p.forall(k % _ != 0)
  } else sys.error(s"can't check: $k")

}

def check(chain: Seq[Int])(implicit p: LinkedHashSet[Int]) = 
  chain.combinations(2).forall { 
    case List(a,b) => 
      isPrime(concat(a,b)) && isPrime(concat(b,a))
  }


def chains(implicit maxLen: Int, symm: Map[Int, Seq[Int]], p: LinkedHashSet[Int]): Set[Seq[Int]] = {
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

def lowestSum(k: Int)(implicit symm: Map[Int, Seq[Int]], p: LinkedHashSet[Int]): Int = {

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
  } { result = chainSum; lowestSeq = lc ++ (mid +: rc); println("hit: " + lowestSeq.mkString(",")) }

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
//solve(4, 10000, 10000)

