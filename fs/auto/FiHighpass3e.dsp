import("stdfaust.lib");

fc = nentry("fc", 0, 0, 1.0, 0.1);

process = fi.highpass3e(fc);
