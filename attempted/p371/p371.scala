import scala.annotation.tailrec

trait State {
  def children: Map[State, Double]
}

object Dead extends State {
  def children = Map(Dead -> 1.0)
}

case class Alive(nnz_unique: Int, n500: Int, nz: Int) extends State {
  def children: Map[State, Double] = {
    // return the possible states that this state can yield after a draw

    // first we just increment nnz_unique:
    val pAllZero = 1d / 1000
    val p500 = 1d / 1000
    val pMissExistingNonZero = (998 - 2*nnz_unique)/1000d
    val pMatchExistingNonZero = nnz_unique / 1000d
    val pHit = nnz_unique / 1000d
    Map(Alive(1+nnz_unique, n500, nz) -> pMissExistingNonZero,
      Alive(nnz_unique, n500, nz) -> pMatchExistingNonZero,
      Alive(nnz_unique, n500, 1+nz) -> pAllZero) ++
        (if(n500 > 0) {
          Map(Dead -> (pHit + p500))
        } else {
          Map(Alive(nnz_unique, 1, nz) -> p500, Dead -> pHit)
        })
  }
}

def update(prior: Map[State, Double]): Map[State, Double] = {
  val posteriorDisassociated = prior.toSeq.flatMap { case (parent, pParent) =>
    parent.children.toSeq.map { case (child, pChild) =>
      child -> (pChild * pParent)
    }
  }

  val grouped = posteriorDisassociated.groupBy { case (state, _) => state }.map {
      case (state, stateProbPairs) =>
        state -> stateProbPairs.unzip._2.sum
    }

  //println(s"pDead == ${grouped(Dead)}")
  //println(s"Sum over states: p == ${grouped.values.sum}")

  grouped
}

def compute: Double = {
  @tailrec
  def _compute(prior: Map[State, Double], result: Double, n: Int, maxN: Int): Double = {
    if(n == maxN) {
      return result
    }

    val posterior = update(prior)

    val deltaPDead = posterior(Dead) - prior(Dead)

    _compute(posterior, result + (1+n)*deltaPDead, 1 + n, maxN)
  }
  
  val prior = Map(Alive(1, 0, 0) -> (998d/1000), Alive(0, 1, 0) -> (1d/1000), Dead -> (1d/1000))

  _compute(prior, 0d, 1, 300)
}


println("Result: %.8f".format(compute))
