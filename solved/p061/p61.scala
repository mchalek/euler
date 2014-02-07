val n = 1 to 1000

def mkItems(f: Int => Int) = { n.map(f).filter(x => x > 999 && x < 10000) }

def permer(items: List[Seq[Int]], cur: List[Int] = List.empty) {
  if(items.isEmpty) {
    if(isCyclic(cur.toSeq)) {
      println(cur.mkString(","))
    }
  } else {
    for {
      q <- items.head
    } {
      permer(items.tail, q::cur)
    }
  }
}

