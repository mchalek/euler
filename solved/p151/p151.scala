import scala.annotation.tailrec

val cuts = IndexedSeq(
  IndexedSeq(-1, 1, 1, 1), // increment when choosing A2
  IndexedSeq(0, -1, 1, 1), // increment when choosing A3
  IndexedSeq(0, 0, -1, 1), // increment when choosing A4
  IndexedSeq(0, 0, 0, -1)) // increment when choosing A5

case class Config(counts: IndexedSeq[Int], singleSheets: Int) {
  require(counts.length == 4, "Too many counts!")
  require(counts.forall(_ >= 0), "Negative count not allowed!" + counts.toString)

  val isFinal = counts.sum == 1 && counts.last == 1

  def isSingle(counts: IndexedSeq[Int]) = {
    counts.sum == 1 && counts.last == 0
  }

  def update(index: Int) = {
    val newCounts = 
      counts.zipWithIndex.map {
        case (count, ind) =>
          count + cuts(index)(ind)
      }

    val newSingleSheet = isSingle(newCounts)

    Config(newCounts, singleSheets + (if(newSingleSheet) 1 else 0))
  }

  def draw: Seq[(Config, Double)] = {
    val total = counts.sum
    val result = counts.zipWithIndex.collect {
      case (count, ind) if count > 0 =>
        (this.update(ind), count.toDouble / total)
    }

    result
  }
}

@tailrec def dive(nodes: Map[Config, Double]): Map[Config, Double] = {
  // input should be a probability distribution over configurations at the
  // current iteration.  normalization is necessary at each level to prevent
  // underflows
  if(nodes.keys.forall(_.isFinal)) {
    return nodes
  }

  val newNodes = collection.mutable.Buffer.empty[(Config, Double)]
  nodes.foreach { case (cfg, wsum) =>
    cfg.draw.foreach {
      case (newCfg, prob) =>
        newNodes += ((newCfg -> (wsum * prob)))
    }
  }

  // must renormalize because the transformation above has norm > 1
  var total = 0d
  val grouped = newNodes.toSeq.groupBy { case (cfg, _) => cfg }.map { 
      case (key, values) => 
        val x = values.unzip._2.sum
        total += x
        (key, x)
      }

  dive(grouped.map { case (k, v) => k -> (v / total) })
}

val initialNodes = Map(Config(IndexedSeq(1,1,1,1), 0) -> 1d)
val result = dive(initialNodes)

var E = 0d
result.foreach { case (cfg, prob) => E += prob * cfg.singleSheets }

println(s"result: $E ~ %.6f".format(E))
