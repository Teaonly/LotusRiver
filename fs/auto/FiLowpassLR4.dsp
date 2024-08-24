import("stdfaust.lib");

cf = nentry("cf", 0, 0, 1.0, 0.1);

process = fi.lowpassLR4(cf);
