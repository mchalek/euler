val n = 1 to 1000

def mkItems(f: Int => Int) = { n.map(f).filter(x => x > 999 && x < 10000) }

def isCyclic(s: List[Int]) = // necessary but not sufficient
  s.forall(i => s.exists(j => i != j && j / 100 == i % 100) && s.exists(j => i != j && i / 100 == j % 100))

def validifier(items: List[Seq[Int]]): List[Seq[Int]] = {
    def validify(l0: Seq[Int], l1: Set[Int]) = {
        val validSuffix = l1.map(x => x / 100)
        val validPrefix = l1.map(x => x % 100)
        l0.filter { x =>
          validPrefix(x / 100) && validSuffix(x % 100)
        }
    }

    for {
        l0 <- items
        l1 = items.diff(List(l0)).flatten.toSet
    } yield validify(l0, l1)
}

def permer(items: List[Seq[Int]], cur: List[Int] = List.empty) {
  if(items.isEmpty) {
    if(isCyclic(cur)) {
      println("%s => %d".format(cur.mkString(","), cur.sum))
    }
  } else {
    for {
      q <- items.head if !cur.contains(q)
    } {
      permer(items.tail, q::cur)
    }
  }
}

val tri = mkItems(m => m*(m+1)/2)
val sq = mkItems(m => m*m)
val pen = mkItems(m => m*(3*m-1)/2)
val hex = mkItems(m => m*(2*m-1))
val hep = mkItems(m => m*(5*m-3)/2)
val oct = mkItems(m => m*(3*m-2))

val items = List(tri,sq,pen,hex,hep,oct)
val reduced = validifier(items)

permer(reduced) // will print a bunch of solutions that are not correct, plus correct one:


