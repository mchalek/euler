case class Edge(nodes: Set[Int], weight: Int)

def parse(filename: String) = {
  val lines = scala.io.Source.fromFile(filename).getLines
  var line_num = 0
  val edges = 
    lines.toIndexedSeq.flatMap { line =>
      val edges = line.split(",").zipWithIndex.collect {
          case (str, ind) if str != "-" =>
              Edge(Set(line_num, ind), str.toInt)
        }

      line_num += 1

      edges
    }.distinct

  (edges.sortBy(e => e.weight), (0 until line_num).toIndexedSeq)
}

def computeSavings(filename: String) = {
  val (graph, graphNodes) = parse(filename)

  val before = graph.map(_.weight).sum

  val (reducedTrees, reducedEdges) =
    graph.foldLeft((graphNodes.map(Set(_)).toSet, Set.empty[Edge])) {
      case ((acc, keep), item @ Edge(nodes, weight)) =>
        val trees = nodes.toSeq.flatMap { n =>
            acc.find(t => t.contains(n))
          }.distinct

        if(trees.length == 1) {
          (acc, keep)
        } else {
          ((acc -- trees) + trees.reduce(_ ++ _), keep + item)
        }
    }

  val after = reducedEdges.toSeq.map(_.weight).sum

  (before, after)
}

val (testBefore, testAfter) = computeSavings("p107_network_test.txt")
println(s"total savings for test network == $testBefore - $testAfter == ${testBefore - testAfter}")

val (before, after) = computeSavings("p107_network.txt")
println(s"total savings for problem network == $before - $after == ${before - after}")
