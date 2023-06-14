Fs = 44000;
c_m = [0,0,0,0,0,0,0,0,0,0,0,1,0];
lengthOf1 = 1;  % TODO
mainVolume = 1; % TODO

values=signal(440, 1000);

sound(values);

tone=makeTone(48, 1, 0.5);
tone

