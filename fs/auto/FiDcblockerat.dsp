import("stdfaust.lib");

fb = nentry("fb", 0, 0, 1.0, 0.1);

process = fi.dcblockerat(fb);
