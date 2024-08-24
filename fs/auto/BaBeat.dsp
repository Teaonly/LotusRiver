import("stdfaust.lib");

bpm = nentry("bpm", 0, 0, 1.0, 0.1);

process = ba.beat(bpm);
