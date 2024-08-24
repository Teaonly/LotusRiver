import("stdfaust.lib");

atk = nentry("atk", 0.1, 0, 10000, 0.01);
hold = nentry("hold", 0.1, 0, 10000, 0.01);
rel = nentry("rel", 0.1, 0, 10000, 0.01);

hold_flag = (rel + hold) * ma.SR;

pos = auto_add ~ _
	with {
		auto_add(last_p, trig) = 
			(trig == 0) * ( ( (last_p - 1) < hold_flag) * (last_p + 1) + ( (last_p + 1) >= hold_flag) * hold_flag);
	};

process(t) = en.are(atk, rel, trig) 
	with {
		p = pos(t);
		trig = (p < hold_flag);
	};

