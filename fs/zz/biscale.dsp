import("stdfaust.lib");

low = nentry("low", 0.1, 0, 10000, 0.01);
up = nentry("up", 0.1, 0, 10000, 0.01);
scale = up - low;

process(x) = low + (xx + 1.0) / 2.0 * scale
	with {
		xx = ((x <= 1.0) & (x >= -1.0)) * x + (x > 1.0) - (x < -1.0);
	};

