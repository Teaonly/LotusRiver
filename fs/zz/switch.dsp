import("stdfaust.lib");

process(a, b, s) = (mode != 0) * a + (mode == 0) * b 
	with {
		mode = p ~ _ with {
			p(x) = (s == 0) * x + (s != 0) * (1 - x);
		};
	};

