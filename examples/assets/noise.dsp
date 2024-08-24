import("stdfaust.lib");

freq = nentry("freq", 0.1, 0, 10000, 0.01);

process = os.osc(freq) * 0.6;
