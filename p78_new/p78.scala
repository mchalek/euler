// direct generation of piles
def countPile(num_left : Int, max_count : Int) : Long = {
  var count : Long = 0
  val stop = if(num_left < max_count) num_left else max_count;
  if(num_left > 0) {
    for(i <- 1 to stop) {
        count += countPile(num_left - i, i);
    }
  } else {
      count = 1
  }

  count
}

val maxN : Int = 1000

println("countPile(5) == " + countPile(5, 5))

var z = 6
val mod : Long = 1000000
var x = countPile(z, z)
while(x % mod != 0) {
  println("not " + z + " (" + x + ")!")
  z += 1
  x = countPile(z, z)
}
