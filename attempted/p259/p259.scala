class p259(maxN: Int) {
  require(1 <= maxN && maxN <= 9, s"Invalid maxN `$maxN`: must be a positive digit")
  sealed trait Item {
    val rep: Char
    val parenDepthUpdate: Int = 0
    val numberDepthUpdate: Int = 0
    val isOperator: Boolean = false
    def allowed(s: State): Boolean = {
      s.items.lastOption.exists {
        // by default allow insertion only if following a number or a close-paren
        case n: Insert => true
        case ParenClose => true
        case _ => false
      }
    }

    override def toString = rep.toString
  }

  class Insert(num: Int) extends Item {
    require(num >= 1 && num <= maxN, s"Positive digits only!")
    override val numberDepthUpdate = 1
    val rep = num.toString.head
    override def allowed(s: State): Boolean = {
      // can always insert / append number except following a close-paren
      s.items.lastOption.forall {
        case ParenClose => false
        case _ => true
      }
    }
  }

  object Plus extends Item {
    val rep = '+'
    override val isOperator = true
  }

  object Minus extends Item {
    val rep = '-'
    override val isOperator = true
  }

  object Times extends Item {
    val rep = '*'
    override val isOperator = true
  }

  object Divide extends Item {
    val rep = '/'
    override val isOperator = true
  }

  object ParenOpen extends Item {
    val rep = '('
    override val parenDepthUpdate = 1
    override def allowed(s: State): Boolean = {
      // allowed at the beginning or after an item
      s.parenDepth + 1 <= s.maxRemainingOperators &&
      s.items.lastOption.forall {
        case o: Insert => false
        case ParenClose => false
        case _ => true
      }
    }
  }

  object ParenClose extends Item {
    val rep = ')'
    override val parenDepthUpdate = -1
    override def allowed(s: State): Boolean = {
      //println(s"evaluating for pclose on ${s.parensContainOperators}")
      s.parensContainOperators.lastOption.exists(identity) &&
      s.items.lastOption.exists {
        case n: Insert => true
        case ParenClose => true
        case _ => false
      }
    }
  }

  val inserters = Range(1, 1 + maxN).map(new Insert(_)).toIndexedSeq
  val nonInserters = Seq(Plus, Minus, Times, Divide, ParenOpen, ParenClose)
  val allowedItems = inserters ++ nonInserters
  val itemLookup = allowedItems.map(o => (o.rep -> o)).toMap

  case class State(
    items: IndexedSeq[Item],
    parensContainOperators: IndexedSeq[Boolean],
    numberDepth: Int,
    parenDepth: Int
  ) {
    val maxRemainingOperators = maxN - numberDepth - 1
    def update(it: Item) = {
      val parensUpdate =
        if(it.isOperator && parenDepth > 0) {
          parensContainOperators.init :+ true
        } else if(it == ParenOpen) {
          parensContainOperators :+ false
        } else if(it == ParenClose) {
          parensContainOperators.init
        } else {
          parensContainOperators
        }

      State(
        this.items :+ it,
        parensUpdate,
        numberDepth + it.numberDepthUpdate,
        parenDepth + it.parenDepthUpdate
      )
    }

    override def toString = {
      items.mkString("") + ")"*parenDepth
    }

  }

  val emptyState = State(IndexedSeq.empty[Item], IndexedSeq.empty[Boolean], 0, 0)

  def analyze(s: String) {
    val (_, isValid) =
      s.foldLeft((emptyState, true)) { case ((state, isValid), opChar) =>
        val op = itemLookup(opChar)
        val allowed = op.allowed(state)
        println(s"$op => $allowed")

        (state.update(op), isValid & allowed)
      }

    if(isValid) {
      println("Sequence is OK")
    } else {
      println("Sequence is not OK")
    }
  }

  private def build(numbers: List[Insert]): Seq[State] = {
    val states = collection.mutable.Buffer.empty[State]

    def buildInternal(numbers: List[Insert], s: State = emptyState) {
      if(numbers.isEmpty) {
        states += s
        return
      }

      if(numbers.head.allowed(s)) {
        buildInternal(numbers.tail, s.update(numbers.head))
      }

      nonInserters.foreach { op =>
        if(op.allowed(s)) {
          buildInternal(numbers, s.update(op))
        }
      }
    }

    buildInternal(numbers)

    states.toSeq
  }

  def countValid: Long = {
    build(inserters.toList).length
  }

  def countSplit: Long = {
    val leftSize = (maxN + 1) / 2
    val leftItems = inserters.take(1 + leftSize).toList
    val rightItems = if(leftSize == maxN) {
      inserters.take(1 + leftSize).toList
    } else {
      inserters.drop(leftSize).reverse.toList
    }

    println(s"left items: $leftItems")
    val left = build(leftItems).groupBy(state => (state.items.last, state.parenDepth))
    println(s"leftGroupedSize: ${left.size}")

    println(s"right items: $rightItems")
    val right = build(rightItems).groupBy(state => (state.items.last, state.parenDepth))
    println(s"rightGroupedSize: ${right.size}")

    var count = 0l
    for {
      (common, init) <- left
      tail <- right.get(common) 
    } {
      count += init.size * tail.size
    }

    count
  }
}

(new p259(9)).analyze("(1/23)*((4*5)-6)*(78-9)")
(new p259(3)).analyze("1/(2*3)")
Seq(1, 2, 3, 4, 5, 6, 7, 8, 9).foreach { maxN =>
  if(maxN < 6) {
    val count = (new p259(maxN)).countValid
    println(s"Count for maxN $maxN: $count")
  } else {
    println(s"Skipping standard count for maxN $maxN")
  }

  val split = (new p259(maxN)).countSplit
  println(s"CountSplit for maxN $maxN: $split")

  println
}
