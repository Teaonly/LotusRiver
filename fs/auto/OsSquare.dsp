import("stdfaust.lib");

freq = nentry("freq", 0, 0, 1.0, 0.1);

process = os.square(freq);
