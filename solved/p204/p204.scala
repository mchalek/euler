// should be able to do meet-in-middle
// one guy exhaust all combos of half of primes
// other guy exhaust other half

// Is an interesting algorithm actually necessary?  This brancher here claims to find the full
// solution in hardly any time!

// this is a good first scala problem i think

def get_maxpow(curr_val : Long, prime : Long, exponent : Int, maxN : Long) : Int = {
  if(curr_val < (maxN/prime))
    get_maxpow(curr_val * prime, prime, exponent + 1, maxN)
  else
    exponent
}

// recursive exhauster
def count_products(primes : Array[Int], maxpow : Array[Int], depth : Int, 
                   max_depth : Long, curr_prod : Long, maxN : Long) : Long = {
  var count : Long = 0
  var local_prod : Long = curr_prod;
  if(depth < max_depth) {
    count += count_products(primes, maxpow, depth + 1, max_depth, curr_prod, maxN); // my prime to power 0
    for(i <- 1 to maxpow(depth)) {
      local_prod *= primes(depth)
      if(local_prod <= maxN)
        count += count_products(primes, maxpow, depth + 1, max_depth, local_prod, maxN);
    }
  } else {
    //println(curr_prod + " is a Hamming number");
    //println(curr_prod);
    count = 1
  }
  
  count
}

val maxN : Long = 1000000000
val maxP : Int = 100
val left_depth: Int = 25;

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

//println(nprimes + " primes from 2 to " + maxP);

val maxpow = new Array[Int](nprimes)

for(i <- 0 to (nprimes-1)) {
  maxpow(i) = get_maxpow(1, primes(i), 0, maxN)
  //println("maxpow[" + primes(i) + "]: " + maxpow(i))
}

println("count of pure Hamming numbers: " + count_products(primes, maxpow, 0, left_depth, 1, maxN))
