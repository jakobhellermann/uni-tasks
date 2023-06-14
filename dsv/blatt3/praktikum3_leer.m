global Fs lengthOf1 m c_m;
Fs = 44100; % Samplerate
lengthOf1 = 0.8; % Dauer einer "ganzen Note" in Sekunden
m = [1 2 3 4 6 8 10 12 14 16 18 20 24]; % Vektor der implementierten Obertöne
c_m = [0 0.7092 0 1 0.2530 0.1794 0.0903 0 0 0 0.1 0.05 0.1];
mainVolume = 0.5;

output = makeTone(44, 0.5, mainVolume);
output = [output makeTone(47, 0.5, mainVolume)];
output = [output makeTone(51, 0.5, mainVolume)];
output = [output makeTone(51, 0.5, mainVolume)];
output = [output makeTone(51, 0.5, mainVolume)];
output = [output makeTone(49, 0.5, mainVolume)];
output = [output makeTone(52, 0.5, mainVolume)];
output = [output makeTone(51, 0.5, mainVolume)];
output = [output makeTone(49, 0.5, mainVolume)];
output = [output makeTone(47, 1.5, mainVolume)];
output = [output makePause(1/32)];
output = [output makeTone(49, 0.5, mainVolume)];
output = [output makeTone(51, 0.5, mainVolume)];
output = [output makeTone(47, 0.5, mainVolume)];
output = [output makeTone(44, 0.5, mainVolume)];
output = [output makeTone(47, 0.5, mainVolume)];
output = [output makeTone(49, 0.5, mainVolume)];
output = [output makeTone(46, 0.5, mainVolume)];
output = [output makeTone(44, 0.5, mainVolume)];
output = [output makeTone(42, 0.5, mainVolume)];
output = [output makeTone(44, 1.5, mainVolume)];

outputPlayer = audioplayer(output, Fs);
playblocking(outputPlayer);

function y = makePause(pauseLength)
    global Fs lengthOf1;
	y = zeros(1, floor(Fs * pauseLength * lengthOf1));
end
