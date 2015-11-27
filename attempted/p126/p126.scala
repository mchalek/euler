import collection.mutable

class Cube(val coords: (Int, Int, Int), sideLen: (Int, Int, Int), faceCovered: Seq[Boolean] = Seq.fill(6)(false)) {
  require(faceCovered.length == 6, "Invalid faceCovered specification!  Must have 6 entries")

  val _faceCovered = faceCovered.toArray

  def setCover(ind: Int) {
    _faceCovered(ind) = true
  }

  lazy val x = coords._1
  lazy val y = coords._2
  lazy val z = coords._3

  lazy val sideX = sideLen._1
  lazy val sideY = sideLen._2
  lazy val sideZ = sideLen._3

  def coverLayer = {
    val result = mutable.Buffer.empty[Cube]
    if(!_faceCovered(0)) {
      result += new Cube((sideX + x, y, z), sideLen, Seq(false, false, false, false, false, true))
    }
    if(!_faceCovered(1)) {
      result += new Cube((x, y, sideZ + z), sideLen, Seq(false, false, false, true, false, false))
    }
    if(!_faceCovered(2)) {
      result += new Cube((x, sideY + y, z), sideLen, Seq(false, false, false, false, true, false))
    }
    if(!_faceCovered(3)) {
      result += new Cube((x, y, z - sideZ), sideLen, Seq(false, true, false, false, false, false))
    }
    if(!_faceCovered(4)) {
      result += new Cube((x, y - sideY, z), sideLen, Seq(false, false, true, false, false, false))
    }
    if(!_faceCovered(5)) {
      result += new Cube((x - sideX, y, z), sideLen, Seq(true, false, false, false, false, false))
    }

    //println(s"""From cube ${this}, generating: ${result.mkString(";")}""")

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

  def +(that: Cube) = {
    for {
      (isCovered, ind) <- that._faceCovered.zipWithIndex if isCovered
    } {
      this.setCover(ind)
    }

    this
  }

  def applyCoverFromCoordSet(coordSet: Set[(Int, Int, Int)]) {
    if(coordSet.contains((x + sideX, y, z))) setCover(0)
    if(coordSet.contains((x, y, z + sideZ))) setCover(1)
    if(coordSet.contains((x, y + sideY, z))) setCover(2)
    if(coordSet.contains((x, y, z - sideZ))) setCover(3)
    if(coordSet.contains((x, y - sideY, z))) setCover(4)
    if(coordSet.contains((x - sideX, y, z))) setCover(5)
  }
}

object CubeHelper {
  def merge(cubes: Seq[Cube]): Seq[Cube] = {
    val (cubeCoords, layer) = cubes.groupBy(cube => cube.coords).toSeq.map { 
      case (coord, cubes) =>
        (coord, cubes.reduce(_+_))
    }.unzip

    val cubeCoordSet = cubeCoords.toSet

    layer.toSeq.foreach(_.applyCoverFromCoordSet(cubeCoordSet))

    layer
  }
}

class Solid(cubes: Seq[Cube]) {
  def volume = cubes.length

  def nextLayer = {
    val nextCubes = cubes.flatMap(_.coverLayer)
    val merged = CubeHelper.merge(nextCubes)

    new Solid(merged)
  }

  override def toString = {
    cubes.mkString(";")
  }
}

object Solid {
  def markCovered(cubes: Seq[Cube]) = {
    val cubeCoordSet = cubes.map(_.coords).toSet

    cubes.foreach(_.applyCoverFromCoordSet(cubeCoordSet))

    cubes
  }

  def _side(n: Int) = if(n % 2 == 0) 2 else 1

  def _min(n: Int) = if(n % 2 == 0) -(n-1) else (-(n-1)/2)

  def _max(n: Int) = if(n % 2 == 0) (n-1) else ((n-1)/2)

  def apply(nx: Int, ny: Int, nz: Int) = {
    val cubes = mutable.Buffer.empty[Cube]
    val sideLengths = (_side(nx), _side(ny), _side(nz))
    for {
      x <- _min(nx) to _max(nx) by sideLengths._1
      y <- _min(ny) to _max(ny) by sideLengths._2
      z <- _min(nz) to _max(nz) by sideLengths._3
    } {
      val center = (x, y, z)
      cubes += new Cube(center, sideLengths)
    }

    new Solid(markCovered(cubes.toSeq))
  }
}

val MAX_N = 200
val counts = mutable.Map.empty[Int, Int]
var x = 1
var solid = Solid(1,1,1)
while(solid.volume <= MAX_N) {
  var y = 1
  while(y <= x && solid.volume <= MAX_N) {
    var z = 1
    while(z <= y && solid.volume <= MAX_N) {
      //println(s"Solid ($x, $y, $z) => ${solid.volume}")
      var layer = 0
      while(solid.volume < MAX_N) {
        if(layer > 0) {
          val prev_count = counts.getOrElseUpdate(solid.volume, 0)
          counts(solid.volume) += 1
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
