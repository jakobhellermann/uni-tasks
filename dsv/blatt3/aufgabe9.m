violin=load("instrument_example.mat");

Fs = violin.Fs_example;
example = violin.example;

spectrum = abs(fft(example));


n = length(example);
f = (0:n-1)*(Fs/n); 
plot(f, spectrum);
xlabel('Frequency')
ylabel('Power')

minpeakheight=10;

findpeaks(spectrum, "MinPeakHeight", minpeakheight)
xlim([0,6000]);
[peaks, locations]=findpeaks(spectrum, "MinPeakHeight", minpeakheight);
freqs=locations.*Fs/n;


basefreq=freqs(1)
baseamp=peaks(1)

m=freqs./basefreq;
c_m=peaks./baseamp;

[m c_m]