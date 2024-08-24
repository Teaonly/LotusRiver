import("stdfaust.lib");

length = nentry("length", 0, 0, 1.0, 0.1);

process = ba.pulse(length);
