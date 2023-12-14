# Instructions

## In Windows

After signing in, search for "ThinLinc-klient" in the search box
in the lower left corner and open it. Enter the server
"thinlinc.student.it.uu.se", and your own username and password.
If you are asked whether you trust this host, click "Continue".
The new window you have is now running on the department's Linux
machines. You can make the window full-screen by clicking the
square in the top-right corner of the window. Avoid pressing the
"x" as this will close your connection!

## In Linux

Open a terminal and immediately write `mkdir kodprov221215`. Go to
this directory with `cd kodprov221215`. Download the code exam to
your computer with the following command:

    curl -L --remote-name http://eliasc.github.io/ioopm/ludo.zip

You now have a zip file with the code for the exam. Unpack it with
`unzip ludo.zip` (and enter the password given in the lab room)
and you will get *another* zip file called `kodprov.zip`.
Unpacking this with `unzip kodprov.zip` will get you a directory
`handout` containing the task to be solved, as well as a
`Makefile` used for handing in the code exam.

## Handing in

Go to the directory `kodprov221215`. If you are unsure about where
you are in the file system you can write `cd; cd kodprov221215`.
Write `make handin` to hand in the code exam. This will create a
zip file containing the file you are supposed to hand in (and no
other files), and this file will be saved in a location where we
can correct it.

## General rules

- The same rules as for a written exam applies: no mobile phones,
  no text messaging, no conversations with anyone except the
  course staff, regardless of medium.
- You must be able to identify yourself.
- You are allowed to bring a hand-written paper (maximum size A4).
  You can write on both sides but cannot bring a magnifying glass.
- You are allowed to bring a book, physically or on a tablet or
  laptop. You are not allowed to run any other programs on this
  machine, and you cannot use them for anything other than reading
  course literature.
- You must write all the code yourself, except the code that is
  given.

# Quacks of Quedlinburg

Quacks of Quedlinburg
(`https://boardgamegeek.com/boardgame/244521/quacks-quedlinburg`)
is a board game where players make potions by mixing ingredients
in a cauldron. Certain ingredients however are volatile, and
adding to many of these will cause the cauldron to explode! The
player who can make the best potion without blowing up is the
winner (actually, the rules are a bit more complicated, but this
will do for this exam).

Ingredients are added to the cauldron one at a time, and each
ingredient comes with a base score. Volatile ingredients
additionally comes with a "volatility score"; if the volatility
score exceeds the capacity of the cauldron, the cauldron explodes.
Depending on which other ingredients are present in the cauldron,
adding an ingredient may have further effects, such as providing
bonus points or negating volatility.

The simplest ingredient is the `Pumpkin`, which simply has a base
score of 1, and no further properties. Your task is to implement
the following three additional ingredients:

- `CherryBomb` -- A cherry bomb can have a base score of 1, 2 or
  3, and comes with a volatility score which is the same as the
  base score.
- `Toadstool` -- A toadstool can have a base score of 1, 2 or 4.
  If there are one or two pumpkins already present in the
  cauldron, a toadstool is worth one additional point. If there
  are three or more pumpkins in the cauldron, a toadstool is worth
  two additional points.
- `Mandrake` -- A mandrake can have a base score of 1, 2 or 4. If
  the last ingredient added before the mandrake was a cherry bomb,
  the volatility of that cherry bomb is negated (only the
  volatility is negated, the score provided by the cherry bomb
  remains).

## The `Cauldron`, `Ingredient` and `Driver` classes

The `Cauldron` class describes a cauldron. A cauldron keeps track
of its ingredients (in a list), its total score and its total
volatility score. If the volatility score exceeds 7, the cauldron
explodes and no further ingredients can be added. The methods
`addToScore()` and `addToVolatility()` are used to update the
respective scores. An ingredient is added using `addIngredient()`.
When this happens, the cauldron first calls the `interact()`
method of that ingredient, passing itself as an argument. This
allows the ingredient to update the score and volatility of the
cauldron according to its properties (note that this is the
visitor pattern that you have seen in assignment 4!). After the
ingredient has interacted with the cauldron, it is added to the
list of ingredients.

The abstract `Ingredient` class acts as the base class for all
ingredients. An ingredient has a base score and a default
implementation of the `interact()` method which simply adds the
base score to the total score of the cauldron. It also provides a
`toString()` method for debugging. The `Pumpkin` class is provided
in its entirety.

You have been given skeleton classes for the other three
ingredients in `Ingredient.java`. Your new ingredients should
override the `interact()` method to provide new behaviour. You
also need to write constructors for these classes. Trying to
create an ingredient with a disallowed base score (see the
previous section) should cause an `InvalidIngredientException` to
be thrown.

**Note! You should only write code in `Ingredient.java`. This is
the only file that will be handed in**

The following example shows some interactions between ingredients
and a cauldron:

```java
Cauldron cauldron = new Cauldron();
assert cauldron.getScore() == 0;
assert cauldron.getVolatility() == 0;

// Adding a pumpkin increases the score by one
cauldron.addIngredient(new Pumpkin());
assert cauldron.getScore() == 1;
assert cauldron.getVolatility() == 0;

// Adding a cherry bomb increases both the score and the volatility
cauldron.addIngredient(new CherryBomb(2));
assert cauldron.getScore() == 3;
assert cauldron.getVolatility() == 2;

// Adding a toadstool gets one bonus point since there is a pumpkin
cauldron.addIngredient(new Toadstool(1));
assert cauldron.getScore() == 5;
assert cauldron.getVolatility() == 2;

// Adding a mandrake directly after a cherry bomb negates its volatility
cauldron.addIngredient(new CherryBomb(3));
assert cauldron.getScore() == 8;
assert cauldron.getVolatility() == 5;

cauldron.addIngredient(new Mandrake(2));
assert cauldron.getScore() == 10;
assert cauldron.getVolatility() == 2;
```

The `Driver` class contains tests for all the ingredients. It will
print the line of the failing test and try to provide helpful
debugging information. In the beginning there will be *a lot* of
failing tests, so you may want to comment out some lines in
`runTests()` to be able to focus on one class at a time. When you
are done you should see the message "All tests passed!". If you
have not commented out any tests, this means that you have
probably passed the code exam.

## Files

- `Ingredient.java` -- You should write your implementation here
- `Cauldron.java` -- The cauldron class. You should not change this file
- `InvalidIngredientException.java` -- The exception thrown when
  trying to create a bad ingredient
- `Driver.java` -- Tests for your ingredients
- `Makefile`  -- A makefile that supports the following targets
  - `all`     -- Compile the program
  - `test`    -- Build and run the tests
  - `clean`   -- Remove any built files

## Pointers

- Each class comes with a dummy constructor to make everything
  compile. You should rewrite these so that they do something
  sensible. Most constructors will look very similar! When
  throwing an `InvalidIngredientException`, the message argument
  is optional but may help debugging.
- The `Cauldron` class implements the `Iterable` interface, which
  means you can iterate over the ingredients of a cauldron with a
  for-each loop:

  `for (Ingredient ingredient : cauldron) { ... }`

  This should be all you need to access the ingredients of a
  cauldron. The order of the ingredients is the order they were
  added in.
- You can identify what kind of ingredient something is by using
  `instanceof`.
- You can subtract from the volatility score by adding a
  *negative* number.