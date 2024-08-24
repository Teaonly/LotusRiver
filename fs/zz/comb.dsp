import("stdfaust.lib");

rtime = nentry("rtime", 0.1, 0, 10000, 0.01);
coef_y = nentry("coef_y", 0.1, 0, 10000, 0.01);
coef_x = nentry("coef_x", 0.1, 0, 10000, 0.01);

n = int(0.25 * ma.SR);
d = int(rtime * ma.SR - 1);

process =  (*(coef_y), *(coef_x) : + : de.delay(n, d)) ~ _;
