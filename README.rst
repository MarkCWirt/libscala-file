A Library for Reading Scala Scale Files
=======================================


**Note**: This project is something of a "hello world." I am interested in 
learning C++ development, so I used this work to create a 
"complete and correct" C++ project, meaning:

- It can be built and installed in a reasonable way. For this I chose CMake.
- It has unit tests and a way to exercise them. Again, I chose CTest (part of 
  CMake).
- I could create a reasonable development environment to work with the code.
  This lies outside the code base, but if you're curious, I chose VS Code, with 
  the ``C/C++``, ``C++ Advanced Linting``, and ``CMake Tools`` extensions. I'm not 
  really a fan of Microsoft products, but VS Code is not horrible (I use it in 
  my day job for Python development).

As such, the code may be a bit wonky.  I believe it works and does what it 
is supposed to, but I don't know if the coding is idiomatic for C++, or even 
what idiomatic C++ code *is*.

About 
-----

``Scala-file`` is a C++ library for reading `scala <http://www.huygens-fokker.org/scala/>`__ 
scale files.  Scala is an Open Source application for working with musical tunings and 
scales.  The scale format has become something of a *de facto* standard for 
describing musical tunings.  This library will read and parse these files. You 
can use it in your C/C++ code to to read these files, should you need to.

Use 
---

::

  #include "scala_file.hpp"

  // Get an open file pointer
  ifstream test_scale;
  test_scale.open("scale.scl");

  // Pass it to read_file to get a scale
  scala::scale loaded_scale = scala::read_file(test_scale);

The return value is a ``scala::scale``, a small interface wrapping 
a vector of the scale degrees.  They can be queried for the 
ratio of the degree. For example, If we passed a 12-TET scale 
to the following code::

    ifstream test_scale;
    test_scale.open("scales/tet-12.scl");
    scala::scale scale = scala::read_file(test_scale);

      for (int i = 0; i < scale.get_scale_length(); i++ ){
        cout << "Degree:  "<< i << " Ratio: " << scale.get_ratio(i) << endl;
    };

we would see the following output:

::

  Degree:  0 Ratio: 1
  Degree:  1 Ratio: 1.05946
  Degree:  2 Ratio: 1.12246
  Degree:  3 Ratio: 1.18921
  Degree:  4 Ratio: 1.25992
  Degree:  5 Ratio: 1.33484
  Degree:  6 Ratio: 1.41421
  Degree:  7 Ratio: 1.49831
  Degree:  8 Ratio: 1.5874
  Degree:  9 Ratio: 1.68179
  Degree:  10 Ratio: 1.7818
  Degree:  11 Ratio: 1.88775
  Degree:  12 Ratio: 2

``get_scale_length()`` and ``get_ratio()`` are the two main functions exposed.

The format for the file itself can be found 
`here <http://www.huygens-fokker.org/scala/scl_format.html>`__ .
The specification is done in English, and there are a few ambiguities.  For 
this implementation I:

- Allow blank lines.  The specification only mentions blank lines being allowed 
  in the description. I allow them to be interspersed, so, for example, a blank line 
  at the middle of the file will not cause problems.
- Allow whitespace before the comment character (``!``). Reading through the specification is 
  sounds as if the comment character has to be in the first column.

Given this, this code should parse all valid Scala files, as they are (perhaps) 
a subset of files that this code can parse.

**If this doesn't suit you**: You can define the macro ``SCALA_STRICT`` in ``scala_file.cpp`` 
to enforce more strict adherence to the standard as detailed.  If you do this

- Comments must begin in the first column
- Only the description can be blank. If further blank lines are encountered it is 
  assumed to be the end of the file, and parsing stops.
- An inability to parse any line results in an error.

If any issues are encountered a run-time error is thrown (in non-strict mode an 
effort is made to continue when unintelligible lines are encountered).

Note that if you do this the TET-12 test will not pass.

The File Format 
---------------

The link above gives the actual specification of the file; this is but a 
brief adumbration.

The file format itself consists of:

- A short one-line description of the file. Can be blank.
- The number of degrees specified in the file. Integer
- A specification line for each degree. 
- Optional comments, denoted by a ``!`` as the first character of the line. 

**Important Note**. In the Scala scale file the initial degree -- which is 
``1`` by default, is implicit.  In the ``scala::scale`` returned this is 
explicit: ``scale.get_ratio(0)`` will always return 1. 

The degree entries can be decimal numbers (which **must** include a decimal point) 
or as a ratio.  Decimal numbers are interpreted as 
`cents <https://en.wikipedia.org/wiki/Cent_(music)>`__ . A number with a 
slash (``/``) is considered a ratio. A bare number is considered a ratio with
a denominator of one.

Given this, a 12-TET scale could be specified as::

    ! 12-TET
    12 tone equal temperament
    12
    !
    100.0
    200.0
    300.0
    400.0
    500.0
    600.0
    700.0
    800.0
    900.0
    1000.0 cents <- An optional label. Ignored.
    1100.0
    1200.0 

A Pythagorean scale could be specified::

    ! Just intonation
    Pythagorean 
    12
    !
    2187/2048
    9/8
    32/27
    81/64
    4/3
    729/512
    3/2
    6561/4096
    27/16
    16/9
    243/128
    2/1




Compiling and Installing 
------------------------

This library uses `CMake <https://en.wikipedia.org/wiki/CMake>`__, so you 
will need that to build and compile. The simplest build install 
cycle is probably

::

    mkdir build
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make
    make test
    sudo make install

``-DCMAKE_BUILD_TYPE=Release`` can be defined if you don't want debugging symbols 
in the library and want optimizations performed.

Note in testing: The tests make liberal use of ``assert()`` to check for 
error conditions. Some compilers (such as GCC) will optimize those asserts 
out in Release mode, making all tests evergreen. You should build in Debug mode 
if you're running the testing target.

The test suite will run seven different input files. They should run without issue
(unless you're compiling in strict mode, in which case six of the tests 
will pass).

By default your system will probably try to install to ``/usr/local``,
but this can be changed be defining ``CMAKE_INSTALL_PREFIX``.
A header file will be written to ``include``, a library archive 
written to ``lib``, and documentation to ``share/doc/libscala-file``.
To uninstall simply delete these files.

::

    Install the project...
    -- Install configuration: "Release"
    -- Installing: /usr/local/share/doc/libscala-file/README.rst
    -- Installing: /usr/local/share/doc/libscala-file/LICENSE.rst
    -- Installing: /usr/local/lib/libscala-file.a
    -- Installing: /usr/local/include/scala_file.hpp
