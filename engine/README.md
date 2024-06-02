### ENGINE OVERVIEW

This is the folder containing the primary engine components. The plan here is to reproduce many game engines concepts of multiple threads handling each aspect of the game. For example an online or P2P game would have a seperate thread for handling the network connections. Additionally a game would have a seperate sound and graphics thread which would have callbacks associated with it which could be interfaced with from any other aspect of the game. This is inspired by Unity's model of having scripts attached to the ingame template objects and systems, though the idea here is to have every entity or process in the game interact with the threads provided by the engine.

The engine is designed to work like an OS kernel. This should allow for the addition of other threads and game aspects in a relatively simple and consistent fashion just as one adds drivers to a kernel or runs user processes which can access kernel features through a system call. The difference is instead of system calls the engine uses multiple threads and the programmer adds callbacks to their objects which call into these threads or vice versa, the programmer can provide a list of functions to the threads which can be called according to any type of control structure they'd like.

### Priority and call order

Due to the asynchronous nature of multi-threaded programs there needs to be some semblence of a call order or priority with objects, or else the system could become completely de-synced and cause lots of graphics or audio buffering. In order to mitigate this there needs to be a certain baseline of functions that get called on timers or __interrupts__. These are provided by the engine and they cannot be called by the programmer, they can however be given structurs containing callback functions which will be called on the programmers behalf with lower priority during each iteration of the engines loop.

### Adding custom threads