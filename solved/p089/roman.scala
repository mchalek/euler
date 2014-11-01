object RomanNumeral {
  val items = Seq(
    "M" -> 1000, "CM" -> 900, "D" -> 500, "CD" -> 400,
    "C" -> 100, "XC" -> 90, "L" -> 50, "XL" -> 40, "X" -> 10,
    "IX" -> 9, "V" -> 5, "IV" -> 4, "I" -> 1)
  def valueToString(value: Int) = {
    var curVal = value
    items.foldLeft("") {
      case (acc, (item, value)) if curVal / value > 0 =>
        val count = curVal / value
        curVal %= value
        acc + item * count
      case (acc, _) => acc
    }
  }

  def stringToValue(str: String): Int = {
    if(str.isEmpty)
      return 0

    val (add, residual) = items.collectFirst {
      case (item, value) if str.startsWith(item) =>
        (value, str.drop(item.size))
    }.getOrElse(sys.error("invalid roman numeral!"))

    add + stringToValue(residual)
  }

  def reduce(in: String): String = valueToString(stringToValue(in))
}

val result = 
  scala.io.Source.fromFile("p089_roman.txt").getLines.map { line =>
    val reduced = RomanNumeral.reduce(line)
    println(s"$line -> $reduced")
    line.length - RomanNumeral.reduce(line).length
  }.sum

println(s"$result characters saved")
