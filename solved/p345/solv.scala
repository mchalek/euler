import scala.io.Source

val matr = Source.fromFile("matr.tsv").getLines.map { line =>
  line.trim.split("\t").map(_.toInt).toSeq
}.toIndexedSeq

val items = matr.foldLeft(Map(Set.empty[Int] -> 0)) { case (acc: Map[Set[Int], Int], row: Seq[Int]) =>
  val updated = row.zipWithIndex.flatMap { case (element: Int, column: Int) =>
    acc.toSeq.collect { case (usedCols: Set[Int], total: Int) if !usedCols(column) =>
        (usedCols + column) -> (total + element)
    }
  }

  updated.groupBy { case (cols, _) => cols }.map {
    case (colSet, pairs) =>
      colSet -> pairs.unzip._2.max
  }
}

require(items.size == 1, "Cannot produce more than one final solution!")
println(s"matr sum: ${items.values.head}")
