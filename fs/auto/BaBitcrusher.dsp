import("stdfaust.lib");

nbits = nentry("nbits", 0, 0, 1.0, 0.1);

process = ba.bitcrusher(nbits);
