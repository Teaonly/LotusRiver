import("stdfaust.lib");

bpm = nentry("bpm", 0.1, 0, 10000, 0.01);

process = ba.beat( bpm * 60.0 );
