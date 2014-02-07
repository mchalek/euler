// kind of a dumb exhaust, with some super-inefficient code mixed in, but
// whatever, runtime < 20 sec
val n = (1 to 1000).toList

def mkItems(f: Int => Int) = { n.map(f).filter(x => x > 999 && x < 10000) }

def isCyclic(s: List[Int]) = // necessary but not sufficient
  s.forall(i => s.exists(j => i != j && j / 100 == i % 100) && s.exists(j => i != j && i / 100 == j % 100))

def validify(l0: List[Int], l1: Set[Int]) = {
    val validSuffix = l1.map(x => x / 100)
    val validPrefix = l1.map(x => x % 100)
    l0.filter { x =>
      validPrefix(x / 100) && validSuffix(x % 100)
    }
}

def validifier(items: List[List[Int]]): List[List[Int]] =
    for {                                                                       
        l0 <- items                                                             
        l1 = items.diff(List(l0)).flatten.toSet                                 
    } yield validify(l0, l1)                                                    

def permer(items: List[List[Int]], cur: List[Int] = List.empty) {
  if(items.isEmpty) {
    if(isCyclic(cur)) {
      println("%s => %d".format(cur.mkString(","), cur.sum))
    }
  } else {
    val validItems = validify(items.head, (cur::(items.tail)).flatten.toSet)
    for {
      q <- validItems if !cur.contains(q)
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

permer(validifier(items)) // will print a bunch of solutions that are not correct because they contain sub-cycles.  manually check or whatever to find:
//1281,2512,8128,2882,5625,8256 => 28684



