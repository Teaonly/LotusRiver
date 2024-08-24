import("stdfaust.lib");

process(a, b, s) = (s != 0) * a + (s == 0)*b;

