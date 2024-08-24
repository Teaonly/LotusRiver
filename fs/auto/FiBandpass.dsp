import("stdfaust.lib");

fl = nentry("fl", 0, 0, 1.0, 0.1);
fu = nentry("fu", 0, 0, 1.0, 0.1);

process = fi.bandpass(2, fl, fu);
