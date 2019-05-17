## Coding Standards for Algorithms and Data Structures

#### Revision History

| ID         | Date     | Comments     |
|------------|----------|--------------|
|1 - Initial |16May2019 |First version |


#### About
The intended purpose of this, and any, coding standard is to reduce the cognative burden of a human analyzing or reading the code. Uniformal and meaningful naming conventions remove any ambiguity about the purpose of a function or the intended use of a variable. Anything beyond reducing the cognative burden or complexity of code is mental masturbation and/or affectation and should not be tolerated by any software engineer with a desire to write clear, understandable code.

#### Rerenced Documents
1.  Joint Strike Figher Air Vehicle C++ Coding Standards for the System Development and Demonstration Program.

#### General
1.  Code should be portable and not rely on any platform, compiler, linker, etc. specific functionality.
2.  Code should be written with clear intent - no 'clever' code or 'code golf' should be introduced.
3.  Test cases using Catch2 should be written for both the happy and unhappy path.
4.  Global variables should be avoided including use of singleton classes.
5.  Encapsulation should be used to reduce exposure of implementation details.
6.  Functions and methods should not exceed 100 logical lines.
7.  Trigraphs will not be used.
8.  Drigraphs will not be used.

#### Preprocessor
1.  Only #ifndef, #define, #endif, and #include preprocessor directives will be used.
2.  #ifndef, #define, #endif directives will only be used as linker guards/prevent multiple inclusion of header files.
3.  #define will be used only as linker guards and never to define constants or inline macros.
4.  #include will be used only to include header (.h) files.

#### Style
1.  Source lines will not exceed 120 characters.
2.  Expressions will exist on a separate line.
3.  Identifiers will not begin with an underscore '\_' character.

#### Naming Convetions
1.  The first letter of a class, struct, enumerated type, or typedef identifier will begin with an upper case letter.
2.  Additional words for the identifer of a class, struct, enumerated type, or typedef will begin with an upper case letter.
3.  All characters in a method or function identifer will be composed of all lower case characters.
4.  Identifiers for constants and enumerated values will be all lower case characters.

#### Classes
1.  Classes should be divided by sections public, protected, and private in that order.
2.  Classes should have no more than 10 data members.
3.  Classes should have no more than 10 member functions.
4.  Functionality of classes should be limited to one operation, e.g. Single Responsability.
5.  All data in a class should be private.
6.  Implicitly generated member functions should be explicitly disallowed.
7.  Member functions that do not alter member data should be delcared const.

#### Blocks
1.  Statements forming the body of if, else, while, do, etc. statements will be enclosed in braces.
2.  Braces in blocks will exist on separate lines.



