import("stdfaust.lib");

//----------------------- VIBRATO ENVELOPE ----------------------------
// 4 phases envelope to control vibrato gain
//
// USAGE:
//   _ : *(envVibrato(b,a,s,r,t)) : _
// where
//   b = beginning duration (silence) in seconds
//   a = attack duration in seconds
//   s = sustain as a percentage of the amplitude to be modified
//   r = release duration in seconds
//   t = trigger signal

envVibrato(b,a,s,r,t) = env ~ (_,_,_) : (!,!,_) // the 3 'state' signals are fed back
    with {
        env(p2,cnt,y) =
            (t>0) & (p2|(y>=1)),
            (cnt + 1)*(t>0), // counter for the first step "b"
            (y + p1*p3*u*(s/100) - p4*w*y)*((p4==0)|(y>=eps))	// y  = envelop signal
            //*(y>=eps) // cut off tails to prevent denormals
        with {
        	p1 = (p2==0) & (t>0) & (y<1) & (cnt>(b*ma.SR)); // p1 = attack phase
        	p3 = 1-(cnt<(nb)); // p3 = beginning phase
        	p4 = (t<=0) & (y>0);  // p4 = release phase
        	// #samples in attack, release, must be >0
        	nb = ma.SR*b+(b==0.0) ; na = ma.SR*a+(a==0.0); nr = ma.SR*r+(r==0.0);
        	// attack and (-60dB) release rates
        	z = s+(s==0.0)*ba.db2linear(-60);
        	u = 1/na; w = 1-1/pow(z*ba.db2linear(60), 1/nr);
        	// values below this threshold are considered zero in the release phase
        	eps = ba.db2linear(-120);
        };
    };

freq = nentry("freq", 0.1, 0, 1000, 0.01);
phase = nentry("phase", 0.1, 0, 1000, 0.01);

attack = nentry("attack", 0.1, 0, 10000, 0.01);
release = nentry("release", 0.1, 0, 10000, 0.01);

process = os.oscp(freq, phase) * envVibrato(0.2 * attack, 0.8 * attack, 60, release);

