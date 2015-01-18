def getSquares = {
  val maxX = 100000
  var x = 1l
  val result = collection.mutable.Buffer.empty[Long]

  while(x < maxX) {
    result += x*x

    x += 1
  }

  result.toSet
}

case class Anagram(w0: String, w1: String) {
  val permutation = getPerm
  val w0Counts = letterCounts(w0)

  private def letterCounts(str: String) = 
    str.distinct.map { letter =>
      str.count(_ == letter)
    }.sorted.toIndexedSeq

  def map(a: Long): Option[Long] = {
    val aStr = a.toString

    if(!check(aStr))
      return None

    //println(s"$a checks out, with $w0 => $w0Counts and $a => ${letterCounts(aStr)}!")
 
    Some(new String(permutation.map(idx => aStr(idx).toChar).toArray).toLong)
  }

  private def check(a: String) = {
    val aCounts = letterCounts(a)

    aCounts == w0Counts
  }

  private def getPerm =
    w1.map { letter =>
      val used = collection.mutable.Set.empty[Int]
      val indices = w0.zipWithIndex.filter { case (ltr, idx) =>
          ltr == letter
        }.unzip._2.toSet

      val result = indices.diff(used).min
      used += result

      result
    }

  override def toString = {
    val pstring = permutation.mkString("")
    s"$w0 ($pstring) $w1"
  }
}

val words = scala.io.Source.fromFile("p098_words.txt").getLines.toIndexedSeq

val countToWords = words.map { word =>
  val letters = word.distinct
  val counts = letters.map { letter => letter -> word.count(_ == letter) }.toSet
  counts -> word
}

val anagrams = countToWords.groupBy(_._1).toIndexedSeq.collect {
  case (_, items) if items.length > 1 =>
    val all = items.unzip._2
    all.combinations(2).toIndexedSeq.map {
      case Seq(a, b) => Anagram(a, b)
    }
}.flatten

val squares = getSquares

val hits = anagrams.flatMap { item =>
  for {
    sq <- squares if sq.toString.length == item.w0.length
    next <- item.map(sq).toSeq if squares(next) && next > sq
    if next.toString.length == sq.toString.length
  } yield {
    (item.w0, item.w1, sq, next)
  }
}

val max = hits.map { case (_, _, _, b) => b }.max

hits.foreach {
  case (s0, s1, a, b) if b == max =>
    println(s"$s0 => $a <--> $b <= $s1 <====== MAX SQUARE NUM == $max")

  case (s0, s1, a, b) =>
    println(s"$s0 => $a <--> $b <= $s1")

  case _ =>
}
