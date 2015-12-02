import scala.annotation.tailrec

trait State {
  def children: Map[State, Double]
}

object Dead extends State {
  def children = Map(Dead -> 1.0)
}

case class Alive(nnz_unique: Int, nz: Int) extends State {
  def children: Map[State, Double] = {
    // return the possible states that this state can yield after a draw

    // first we just increment nnz_unique:
    val pAllZero = 1d / 1000
    val pMissExistingNonZero = (999 - 2*nnz_unique)/1000d
    val pMatchExistingNonZero = nnz_unique / 1000d
    val pHit = nnz_unique / 1000d
    Map(Alive(1+nnz_unique, nz) -> pMissExistingNonZero,
      Alive(nnz_unique, nz) -> pMatchExistingNonZero,
      Alive(nnz_unique, 1+nz) -> pAllZero,
      Dead -> pHit)
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
  
  val prior = Map(Alive(1, 0) -> (999d/1000), Dead -> (1d/1000))

  _compute(prior, 0d, 1, 400)
}


println("Result: %.9f".format(compute))
