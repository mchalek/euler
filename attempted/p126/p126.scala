import collection.mutable

class Cube(val x: Int, val y: Int, val z: Int, faceCovered: Seq[Boolean] = Seq.fill(6)(false)) {
  require(faceCovered.length == 6, "Invalid faceCovered specification!  Must have 6 entries")

  def cover = {
    val result = mutable.Buffer.empty[Cube]
    if(!faceCovered(0)) {
      result += new Cube(1 + x, y, z, Seq(false, false, false, false, false, true))
    }
    if(!faceCovered(1)) {
      result += new Cube(x, y, 1 + z, Seq(false, false, false, true, false, false))
    }
    if(!faceCovered(2)) {
      result += new Cube(x, 1 + y, z, Seq(false, false, false, false, true, false))
    }
    if(!faceCovered(3)) {
      result += new Cube(x, y, z - 1, Seq(false, true, false, false, false, false))
    }
    if(!faceCovered(4)) {
      result += new Cube(x, y - 1, z, Seq(false, false, true, false, false, false))
    }
    if(!faceCovered(5)) {
      result += new Cube(x - 1, y, z, Seq(true, false, false, false, false, false))
    }

    result.toSeq
  }

  override def toString = {
    s"""($x, $y, $z)"""
  }

  override def equals(that: Any) = {
    that match {
      case cube: Cube => cube.x == x && cube.y == y && cube.z == z
      case _ => false
    }
  }

  override def hashCode = {
    (x, y, z).hashCode
  }
}

object CubeHelper {
  def merge(cubes: Seq[Cube]): Seq[Cube] = {
    val cubeCoordSet = cubes.map(cube => (cube.x, cube.y, cube.z)).toSet

    cubeCoordSet.toSeq.map { case (x, y, z) =>
      val newCovered = Seq(
        cubeCoordSet.contains((x + 1, y, z)),
        cubeCoordSet.contains((x, y, z + 1)),
        cubeCoordSet.contains((x, y + 1, z)),
        cubeCoordSet.contains((x, y, z - 1)),
        cubeCoordSet.contains((x, y - 1, z)),
        cubeCoordSet.contains((x - 1, y, z)))

      new Cube(x, y, z, newCovered)
    }
  }
}

class Solid(cubes: Seq[Cube], innerVolume: Int = 0) {
  def volume = cubes.length
  def outerLayer = volume - innerVolume

  def nextLayer = {
    val nextCubes = cubes.flatMap(_.cover)
    val merged = CubeHelper.merge(cubes ++ nextCubes)

    new Solid(merged, volume)
  }

  override def toString = {
    cubes.mkString(";")
  }
}

object Solid {
  def isCovered(value: Int, lowerUpper: Boolean, N: Int) = {
    if(N == 1)
      false
    else {
      if(!lowerUpper) {
        value == 0
      } else { 
        value == N-1
      }
    }
  }

  def apply(nx: Int, ny: Int, nz: Int) = {
    val cubes = mutable.Buffer.empty[Cube]
    for {
      x <- 0 until nx
      y <- 0 until ny
      z <- 0 until nz
    } {
      val covered = Seq(isCovered(x, false, nx), isCovered(z, false, nz), isCovered(y, false, ny),
        isCovered(z, true, nz), isCovered(y, true, ny), isCovered(x, true, nx))
      cubes += new Cube(x, y, z, covered)
    }

    new Solid(cubes.toSeq)
  }
}

val MAX_N = 200
val counts = mutable.Map.empty[Int, Int]
var x = 1
var solid = Solid(1,1,1)
while(solid.outerLayer <= MAX_N) {
  var y = 1
  while(y <= x && solid.outerLayer <= MAX_N) {
    var z = 1
    while(z <= y && solid.outerLayer <= MAX_N) {
      //println(s"Solid ($x, $y, $z) => ${solid.outerLayer}")
      var layer = 0
      while(solid.outerLayer < MAX_N) {
        if(layer > 0) {
          val prev_count = counts.getOrElseUpdate(solid.outerLayer, 0)
          counts(solid.outerLayer) += 1
        }

        layer += 1
        solid = solid.nextLayer
      }

      z += 1
      solid = Solid(x, y, z)
    }

    y += 1
    solid = Solid(x, y, 1)
  }

  x += 1
  solid = Solid(x, 1, 1)
}

val test_values = Seq(22,46, 78, 118,154)
test_values.foreach { value =>
  println(s"C($value) == ${counts.getOrElse(value, 0)}")
}

println(s"Max C: ${counts.values.toSeq.max}")
