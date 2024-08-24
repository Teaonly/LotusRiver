import("stdfaust.lib");

p = nentry("p", 0, 0, 1.0, 0.1);

process = fi.pole(p);
