function s = makeTone(n, length, volume)
    global lengthOf1;
    global mainVolume;

    l = length * lengthOf1;
    v = volume * mainVolume;

    f = F_n(n);

    s = signal(f, l) * v;
end

function f = F_n(n)
    f_a1 = 440;
    f = 2^((n-49)/12) * f_a1;
end