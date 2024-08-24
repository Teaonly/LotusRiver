import("stdfaust.lib");

bw = nentry("bw", 0.1, 0, 10000, 0.01);

process(x,fc) = x:fi.bandpass(1, fc - bw / 2, fc + bw /2 );

