import("stdfaust.lib");

cf = nentry("cf", 0, 0, 1.0, 0.1);

process = fi.highpassLR4(cf);
