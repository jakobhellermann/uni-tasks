function [values] = signal(f_n,length)
    global Fs;
    global c_m;
    
    ms = [1,2,3,4,6,8,10,12,14,16,18,20,24];
    
    omega_0 = 2*pi*Fs; % is this correct?

    values = arrayfun(@(t)sum(sin(ms * omega_0 * t) .* c_m), 1:length);
end

