<h2>Overview</h2>
This is a Sh'mup engine written in C/C++ to be programmed to ATMega1284 chips and an Arduino respectively. However, due to time constraints and hardware limitations, the original project was scrapped in favor of a more basic game with lasers serving as its only projectile, rendering the project in an incomplete form. The UI and control logic is programmed on the ATMega1284 chips (written in C), while the game logic itself is written on an Arduino UNO (written in C++).

<h2>Design</h2>
*Disclaimer: I am not implying this is a good design. I am merely explaining how I designed it on a whim without any advising.

This is designed with class-objects being driven by state machines. After each frame, each object would update and the screen would render each class-object's new state.
The state machine design is written in respect to Frank Vahid's method of implementation. In a general sense, every task would have its own state machine that ticked after a specified period, over an automatically calculated hyper-period. This was originally taught in C for the ATMega1284 in class.
However, as the game logic had to be written on the Arduino, which operated in C++, I figured I could make use of classes and inheritance in C++ that C lacked. Therefore, I made each task into a class - a game object. Static variables which were originally declared in the Tick() function became encapsulated as member variables. The Tick() for that task would be a public member function. Once I did that, I found myself with classes that operated very similarly to game-objects used in existing game engines.

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

<h2>Potential Future Improvements</h2>

<h2>How to use the Code</h2>
This code is not for practical use, nor would it be very functional. It was uploaded solely for the purpose of archiving a project, in hopes of being revived again some day when I find the time. Until then, it will remain incomplete.
