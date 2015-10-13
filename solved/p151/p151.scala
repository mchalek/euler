import scala.annotation.tailrec

val cuts = IndexedSeq(
  IndexedSeq(-1, 1, 1, 1, 1), // increment when choosing A1
  IndexedSeq(0, -1, 1, 1, 1), // increment when choosing A2
  IndexedSeq(0, 0, -1, 1, 1), // increment when choosing A3
  IndexedSeq(0, 0, 0, -1, 1), // increment when choosing A4
  IndexedSeq(0, 0, 0, 0, -1)) // increment when choosing A5

case class Config(counts: IndexedSeq[Int], singleSheets: Int) {
  require(counts.length == 5, "Too many counts!")
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

  def getTerminalProbabilities = {
    @tailrec def dive(nodes: Map[Config, Double]): Map[Config, Double] = {
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

      val grouped = newNodes.toSeq.groupBy { case (cfg, _) => cfg }.map { 
          case (key, values) => (key, values.unzip._2.sum)
        }

      dive(grouped)
    }
    dive(Map(this -> 1d))
  }
}

val probabilities = Config(IndexedSeq(1,0,0,0,0), 0).getTerminalProbabilities

var E = 0d
probabilities.foreach { case (cfg, prob) => E += prob * cfg.singleSheets }

println(s"result: $E ~ %.6f".format(E))
