import("stdfaust.lib");

fc = nentry("fc", 0, 0, 1.0, 0.1);

process = fi.bandpass6e(fc);
