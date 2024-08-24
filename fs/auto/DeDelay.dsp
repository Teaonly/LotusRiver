import("stdfaust.lib");

d = nentry("d", 0, 0, 1.0, 0.1);

process = de.delay(8192, d);
