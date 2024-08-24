import("stdfaust.lib");

cx = nentry("cx", 0.1, 0, 1, 0.01);
cy = 1.0 - cx;

process(x) = (*(cy), cx*x : +) ~ _;

