import collection.mutable

class Cube(coords: (Int, Int, Int), faceCovered: Seq[Boolean] = Seq.fill(6)(false)) {
  require(faceCovered.length == 6, "Invalid faceCovered specification!  Must have 6 entries")

  val _faceCovered = faceCovered.toArray

  def setCover(ind: Int) {
    _faceCovered(ind) = true
  }

  def x = coords._1
  def y = coords._2
  def z = coords._3


  def coverLayer = {
    val result = mutable.Buffer.empty[Cube]
    if(!_faceCovered(0)) {
      result += new Cube((1 + x, y, z), Seq(false, false, false, false, false, true))
    }
    if(!_faceCovered(1)) {
      result += new Cube((x, y, 1 + z), Seq(false, false, false, true, false, false))
    }
    if(!_faceCovered(2)) {
      result += new Cube((x, 1 + y, z), Seq(false, false, false, false, true, false))
    }
    if(!_faceCovered(3)) {
      result += new Cube((x, y, z - 1), Seq(false, true, false, false, false, false))
    }
    if(!_faceCovered(4)) {
      result += new Cube((x, y - 1, z), Seq(false, false, true, false, false, false))
    }
    if(!_faceCovered(5)) {
      result += new Cube((x - 1, y, z), Seq(true, false, false, false, false, false))
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

  def +(that: Cube) = {
    for {
      (isCovered, ind) <- that._faceCovered.zipWithIndex if isCovered
    } {
      this.setCover(ind)
    }

    this
  }
}

object CubeHelper {
  def merge(cubes: Seq[Cube]): Seq[Cube] = {
    val (cubeCoords, layer) = cubes.groupBy(cube => (cube.x, cube.y, cube.z)).toSeq.map { 
      case (coord, cubes) =>
        (coord, cubes.reduce(_+_))
    }.unzip

    val cubeCoordSet = cubeCoords.toSet

    layer.toSeq.foreach { cube =>
      val (x, y, z) = (cube.x, cube.y, cube.z)
      if(cubeCoordSet.contains((x + 1, y, z))) cube.setCover(0)
      if(cubeCoordSet.contains((x, y, z + 1))) cube.setCover(1)
      if(cubeCoordSet.contains((x, y + 1, z))) cube.setCover(2)
      if(cubeCoordSet.contains((x, y, z - 1))) cube.setCover(3)
      if(cubeCoordSet.contains((x, y - 1, z))) cube.setCover(4)
      if(cubeCoordSet.contains((x - 1, y, z))) cube.setCover(5)
    }

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
      cubes += new Cube((x, y, z), covered)
    }

    new Solid(cubes.toSeq)
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
