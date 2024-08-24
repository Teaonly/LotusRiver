import("stdfaust.lib");

attack = nentry("attack", 0, 0, 1.0, 0.1);
release = nentry("release", 0, 0, 1.0, 0.1);

process = en.are(attack, release);
