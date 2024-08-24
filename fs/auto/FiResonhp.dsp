import("stdfaust.lib");

fc = nentry("fc", 0, 0, 1.0, 0.1);
q = nentry("q", 0, 0, 1.0, 0.1);
gain = nentry("gain", 0, 0, 1.0, 0.1);

process = fi.resonhp(fc, q, gain);
