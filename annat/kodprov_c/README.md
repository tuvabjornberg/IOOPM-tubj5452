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

Open a terminal and immediately write `mkdir kodprov231025`. Go to
this directory with `cd kodprov231025`. Download the code exam to
your computer with the following command:

    curl -L --remote-name http://eliasc.github.io/ioopm/bulle.zip

You now have a zip file with the code for the exam. Unpack it with
`unzip bulle.zip` (and enter the password given in the lab room)
and you will get *another* zip file called `kodprov.zip`.
Unpacking this with `unzip kodprov.zip` will get you a directory
`handout` containing the task to be solved, as well as a
`Makefile` used for handing in the code exam.

## Handing in

Go to the directory `kodprov231025`. If you are unsure about where
you are in the file system you can write `cd; cd kodprov231025`.
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

# Internal Iterators

A linked list is a dynamic data structure that allows arbitrary
indexing. However, it is not very efficient since every access to
the list needs to traverse the entire list from the beginning. A
common solution to this is an *iterator*, which remembers a
position in the list and allows accessing that position in
constant time.

Iterators can be *internal* or *external*. An external iterator is
an additional data structure external to the list, meaning you can
have several iterators in the same list at the same time. An
internal iterator on the other hand is part of the list, meaning
only a single position can be remembered at a time in the list.
The focus of this code exam is a special kind of internal
iterators that remembers the last accessed index and allows fast
insertion and deletion from that point. For simplicity, we remove
the ability to actually move the iterator forward.


## A Latest-Position Iterator for a Linked List

The file `list.h` defines the interface for a linked list data
type `list_t`. The file `list.c` contains a partial implementation
of the linked list, and your job is to finish it. You need to make
two changes to the existing code:

- Change the `list` struct so that it allows remembering the
  latest position accessed, for example by adding an additional
  pointer field to the struct, below called the "remembered
  pointer".
- Change the function `list_get` so that it updates the remembered
  pointer on a successful list access. Note that you should *not*
  change the function `list_insert`.

Because you will want to be able to insert and remove elements at
the latest accessed position, the remembered pointer should point
to the *previous* link of the latest accessed position. For
example, when accessing index 3, the remembered pointer should
point to the link at index 2. If the latest accessed position was
at index 0, the pointer should be `NULL`.

**Note that you should only update the remembered pointer if the
call to `list_get` was successful. If the list is indexed out of
bounds, this should not affect the remembered pointer.**

Next, you need to implement functions for adding and removing
elements at the remembered pointer:

- The function `list_insert_at_latest` inserts an element at the
  latest accessed index, i.e. after the link pointed to by the
  remembered pointer. If the remembered pointer is `NULL`, the
  element should be inserted at the front of the list.
- The function `list_remove_at_latest` should remove and return
  the element at the latest accessed index (or the first if the
  remembered pointer is `NULL`). If there are no more elements to
  remove at the latest accessed index, the function should return
  `NULL`.

Repeated calls to either function should keep adding or removing
elements at the same index. For example, if the latest accessed
index of a list `l` was 3, a call to `list_insert_at_latest(l, "foo")`
should insert `"foo"` at index 3, and a subsequent call to
`list_insert_at_latest(l, "bar")` should insert `"bar"` at index
3 as well, moving the `"foo"` element to index 4.

**Note that there are hints at the end of this document for how to
implement all of this**

The following code shows a simple interaction with the
latest-position iterator:

```c
list_t *l = list_create();
list_insert(l, "a", 0);
list_insert(l, "small", 1);
list_insert(l, "dog", 2);

// Latest position should be 0 (since get was not called yet)

list_insert_at_latest(l, "pet");
// List is now ["pet", "a", "small", "dog"]

// Set the latest position to 2
list_get(l, 2);

list_insert_at_latest(l, "very");
list_insert_at_latest(l, "very");
// List is now ["pet", "a", "very", "very", "small", "dog"]

// Set the latest position to 4
list_get(l, 4);

list_remove_at_latest(l); // returns "small"
list_remove_at_latest(l); // returns "dog"
list_remove_at_latest(l); // returns NULL

// List is now ["pet", "a", "very", "very"]

// Cleanup
list_destroy(l);
```

When you are done, you should be able to run the tests through
valgrind without any memory errors or leaks.

## Files

- `list.h` -- The interface you should implement
- `list.c` -- You should write your implementation here
- `list_test.c` -- Tests for your library
- `Makefile`  -- A makefile that supports the following targets
  - `all`     -- Compile the program
  - `run`     -- Build and run the `main` function in `list.c`
  - `test`    -- Build and run the tests
  - `memrun` -- Build and run the `main` function in `list.c` with valgrind
  - `memtest` -- Build and run the tests with valgrind
  - `clean`   -- Remove any built files

Note that you can write tests of your own in the existing `main`
function of `list.c` and run it with `make run`. The code in
the `main` function will not be assessed.

## Hints

- Running the tests with the handed out code causes a segmentation
  fault in the tests for `list_insert_at_latest`. This is to be
  expected since this function doesn't actually insert anything,
  meaning that `list_get` will index out of bounds and return
  `NULL`.
- Start by writing the code that remembers the latest position.
  The extension to `list_get` should not need to be more than
  three lines. Note how this is similar to `find_previous_entry`
  that you wrote for assignment 1! You can test this function by
  writing a helper function that prints the element of the
  remembered pointer.
- The code for `list_insert_at_latest` can be as simple as an if
  statement with one line per branch: if the remembered pointer is
  `NULL`, insert at the beginning of the list, otherwise insert
  after the remembered pointer.
- The code for `list_remove_at_latest` is more involved. There are
  four cases:
  1. The list is empty, so we return `NULL`,
  2. The remembered pointer is `NULL`, so we remove from the front
     of the list,
  3. The remembered pointer is at the end of the list, so we
     return `NULL`,
  4. The remembered pointer points to a link in the middle of the
     list, so we remove the following link and return its element.
