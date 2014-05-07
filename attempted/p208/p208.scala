import scala.annotation.tailrec
import scala.collection.breakOut

case class State(x: Double, y: Double, heading: Int) {
  def tol = 1e-7
  override def equals(a: Any) =
    a match {
      case State(ax, ay, ah) => math.abs(ax-x) < tol && math.abs(ay-y) < tol && ah == heading
      case _ => false
    }

  val ix = math.round(x*1e6)
  val iy = math.round(y*1e6)

  override def hashCode = ix.hashCode ^ iy.hashCode ^ heading.hashCode

  def possible(implicit deltas: Map[Int, IndexedSeq[(Double, Double, Int)]]): Seq[State] =
    deltas(heading) match {
      case IndexedSeq((dx0, dy0, nh0), (dx1, dy1, nh1)) =>
        Seq(State(x + dx0, y + dy0, nh0), State(x + dx1, y + dy1, nh1))
      case _ => sys.error("Could not find valid increment in deltas table!")
    }

  def complement = State(-x, -y, 5-heading)
}

object P208 {
  def computeDeltas(polySides: Int): Map[Int, IndexedSeq[(Double, Double, Int)]] = {
    require(360 % polySides == 0, "For now we only support polygons with integer (degree) arc angles!")

    val arcAngle = 360 / polySides

    (0 until polySides).map { s =>
      import math._

      s -> IndexedSeq(s+1, s+polySides-1).map(_ % polySides).map { case newHeading =>
        val arc = newHeading*arcAngle
        val dx = cos(toRadians(arc))
        val dy = sin(toRadians(arc))

        (dx, dy, newHeading)
      }
    }(breakOut)
  }

  @tailrec def pathCounts(
    maxSteps: Int,
    prev: Map[State, Long] = Map(State(0.0,0.0,0) -> 1),
    numSteps: Int = 0)(
    implicit deltas: Map[Int, IndexedSeq[(Double, Double, Int)]]): Map[State, Long] = {

    if(numSteps == maxSteps)
      return prev

    val condensed = scala.collection.mutable.Map.empty[State, Long]

    prev.foreach { case (state, count) =>
      val possible = state.possible
      possible.foreach { s => 
        val old = condensed.getOrElse(s, 0l)
        condensed(s) = old + count
      }
    }

    //println(s"${condensed.size} possible states at depth ${1 + numSteps}.  diving deeper!")
    pathCounts(maxSteps, condensed.toMap, 1 + numSteps)
  }

  def countClosedPaths(maxSteps: Int)(implicit deltas: Map[Int, IndexedSeq[(Double, Double, Int)]]): Long =
    pathCounts(maxSteps).getOrElse(State(0.0, 0.0, 0), 0)

  def splitCountClosedPaths(
    polySides: Int,
    maxSteps: Int)(
    implicit deltas: Map[Int, IndexedSeq[(Double, Double, Int)]]): Long = {
      require(maxSteps % 2 == 0, "Split count method only works with even maxSteps!")

      val headingPaths = (0 until polySides).map { h0 =>
        h0 -> pathCounts(maxSteps / 2, Map(State(0.0, 0.0, h0) -> 1))
      }.toMap
      
      val target = State(0.0, 0.0, 0)
      headingPaths(0).foldLeft(0l) { case (acc, (fwdState, count)) =>
        val revState = fwdState.complement
        val revCount =
          headingPaths(fwdState.heading).getOrElse(revState.copy(heading=0), 0l)

        acc + count * revCount
      }
  }
}

val polygonSides = 5
val pathLength = 70
val deltas = P208.computeDeltas(polygonSides)
//val closedPaths = P208.countClosedPaths(pathLength)(deltas)
val splitClosedPaths = P208.splitCountClosedPaths(polygonSides, pathLength)(deltas)
//println(s"$closedPaths closed paths of length $pathLength")
println(s"solution via split method: $splitClosedPaths")
