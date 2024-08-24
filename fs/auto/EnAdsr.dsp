import("stdfaust.lib");

attack = nentry("attack", 0, 0, 1.0, 0.1);
decay = nentry("decay", 0, 0, 1.0, 0.1);
sustain = nentry("sustain", 0, 0, 1.0, 0.1);
release = nentry("release", 0, 0, 1.0, 0.1);

process = en.adsr(attack, decay, sustain, release);
