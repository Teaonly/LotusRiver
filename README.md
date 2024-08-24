# LotusRiver 
An stacked, vectorized audio synthesizer.

Some design ruler:

* vector signal in vector signal out
* scalar in scalar out
* vectout output scalar with block size = 1
* ordered operation/inputs left pop first ( LPF )
* parameters is right pop first ( RPF ), so left to right order in code. 
* some basic operators support broadcast
* user defined words support closure with local hashmap
