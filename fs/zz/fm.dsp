import("stdfaust.lib");

carry = nentry("carry", 0.1, 0, 10000, 0.01);
modulator = nentry("modulator", 0.1, 0, 10000, 0.01);
index = nentry("index", 0.1, 0, 1000, 0.01);

freqs = (carry, modulator);
indics = (index); 
process = sy.fm(freqs, indics);
