import("stdfaust.lib");

d = nentry("d", 0, 0, 1.0, 0.1);

process = de.fdelay(8192, d);
