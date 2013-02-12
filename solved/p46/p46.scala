def goldsum(prime: Int, sqrt: Int) : Int = {
  prime + 2*sqrt*sqrt
}

val maxP : Int = 1000000

// first prime sieve
var iscomp = new Array[Boolean](maxP + 1); // is number composite?
var primes = new Array[Int](maxP + 1);
var nprimes : Int = 0;

for(i <- 0 to maxP)
  iscomp(i) = false

for(i <- 2 to maxP) {
  if(iscomp(i) == false) {
    primes(nprimes) = i;
    nprimes += 1
    for(j <- (2*i) to maxP by i) {
      iscomp(j) = true
    }
    //println(i + " is prime")
  }
}

println("primes generated from 2 to " + maxP)

var GoldPass = new Array[Boolean](maxP + 1)
for(i <- 9 to maxP) {
  GoldPass(i) = false
}

println("GoldPass initialized!")

for(i <- 0 to nprimes) {
  var j = 1
  while(goldsum(primes(i), j) < maxP) {
    GoldPass(goldsum(primes(i), j)) = true
    j += 1
  }
}

for(i <- 9 to maxP by 2) {
  if(iscomp(i) && !GoldPass(i))
    println("Solution!  " + i)
}
