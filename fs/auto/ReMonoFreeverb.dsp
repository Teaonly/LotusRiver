import("stdfaust.lib");

fb1 = nentry("fb1", 0, 0, 1.0, 0.1);
fb2 = nentry("fb2", 0, 0, 1.0, 0.1);
damp = nentry("damp", 0, 0, 1.0, 0.1);
spread = nentry("spread", 0, 0, 1.0, 0.1);

process = re.mono_freeverb(fb1, fb2, damp, spread);
