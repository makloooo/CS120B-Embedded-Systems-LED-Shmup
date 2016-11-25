<h2>Overview</h2>
This is a Sh'mup engine written in C/C++ to be programmed to ATMega1284 chips and an Arduino respectively. However, due to time constraints and hardware limitations, the original project was scrapped in favor of a more basic game with lasers serving as its only projectile, rendering the project in an incomplete form. The UI and control logic is programmed on the ATMega1284 chips (written in C), while the game logic itself is written on an Arduino UNO (written in C++). Each game-object has animations.

<h2>Design</h2>
*Disclaimer: I am not implying this is a good design. I am merely explaining how I designed it on a whim without any advising.

This is designed with class-objects being driven by state machines. After each frame, each object would update and the screen would render each class-object's new state.
The state machine design is written in respect to Frank Vahid's method of implementation. In a general sense, every task would have its own state machine that ticked after a specified period, over an automatically calculated hyper-period. This was originally taught in C for the ATMega1284 in class.
However, as the game logic had to be written on the Arduino, which operated in C++, I figured I could make use of classes and inheritance in C++ that C lacked. Therefore, I made each task into a class --- a game object. Static variables which were originally declared in the Tick() function became encapsulated as member variables. The Tick() for that task would be a public member function. Once I did that, I found myself with classes that operated very similarly to game-objects used in existing game engines.

In terms of wiring, I mainly had trouble managing packing dropping during communication between micro-processors. Two ATMega1284 micro-processors communicated between each other using USART communication. Those two also communicated with the Arduino UNO; with varying success.

<h2>Hardware Modules</h2>
+ 1 LCD Screen
+ 2 LED Bars
+ 2 ATMega1284 Micro-processors
+ 3 Shift Registers
+ 1 Quad-Directional Switch
+ 1 Arduino UNO
+ 1 32x32 LED Matrix

<h2>Shortcomings</h2>
In terms of shortcomings, there were plenty that led to the project being scrapped and downgraded to an inferior version.

First and foremost, the most fundamental problem was dealing with bit dropping. The UNO also takes up a large majority of its memory to run the LED matrix, so I had originally intended to write the game logic and object management on the ATMega1284, which has a larger amount of SRAM on it than the ATMega323 (the chip embedded in an UNO). The ATMega would feed the updated positions of each object into the UNO, which would render the object on the screen. However, with bit dropping, communication would become unsynchronized, and the matrix would draw the screen incorrectly. I could not figure out a way to fix synchronization with the time constraints, so I went with a more straightforward approach to program the logic directly onto the Arduino UNO.

However, the problem with that was the UNO running out of SRAM. I had to scrap many features of what I had planned because of the SRAM limitations on the UNO. Like explained, the UNO takes up a large amount of SRAM memory with operating the 32x32 LED Matrix, so it could not have possibly held an entire game's worth of logic in the microchip. I had to reduce the amount of active objects on screen, and allocate memory to only four laser-type projectiles, and one player object. I optimized to the best of my ability, but this problem could not be solved with programming alone.

A smaller problem would be that the Arduino UNO is not exactly the best for computational time. I had to decide to only use the 'Laser' type projectile in the end, leaving the rest of the types unused. The drawLine() function provided by the Adafruit 32x32 matrix library needs a notable amount of computational time. Redrawing a several lines, calculating the states of all other objects exceeded the necessary period to have a smooth frame rate --- leading to timer overrun.

Overall, all of this could have been avoided with more careful planning. However, it was the first time I've ever managed a project on my own. I gained an invaluable amount of experience from this despite not being able to complete it on time.

<h2>Potential Future Improvements</h2>

<h2>How to use the Code</h2>
This code is not for practical use, nor would it be very functional. It was uploaded solely for the purpose of archiving a project, in hopes of being revived again some day when I find the time. Until then, it will remain incomplete.

<h2>CS120B Lab Report</h2>
For reference, you may refer to the lab report requried to be written. It is uploaded on the repository as *CS120B Custom Project Lab Report*. It contains indepth detail about the code as well as a picture of the wiring.
