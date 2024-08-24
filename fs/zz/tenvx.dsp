import("stdfaust.lib");

atk = nentry("atk", 0.1, 0, 10000, 0.01);
hold = nentry("hold", 0.1, 0, 10000, 0.01);
rel = nentry("rel", 0.1, 0, 10000, 0.01);

a_a = exp(-1.0/(atk * ma.SR));
b_a = 1.0 - a_a;
a_r = exp(-1.0/(rel * ma.SR));
hcount = hold * ma.SR;

counter(t) = (a * hcount + b * (_ - 1) )  ~ check  
	with {
		a = t != 0;
		b = t == 0;
		check(x) = (x > 0) * x;
	};

process(t) = select ~ _
	with {
		count = counter(t);
		select(y) = (count > 0) * (b_a + a_a * y) + (count <= 0) * a_r * y;
	};

