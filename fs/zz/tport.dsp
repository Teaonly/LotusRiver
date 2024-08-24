import("stdfaust.lib");

cx = nentry("cx", 0.1, 0, 1, 0.01);

cy = 1.0 - cx;

with_trig(t, x) = _ * t + (1.0 - t) * x;

process(t, x) = (*(cy), x*cx : +) ~ with_trig(tt, x) 
	with {
		tt = t == 0;	
	};

