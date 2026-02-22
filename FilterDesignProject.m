%Bailey Brown
%1001555076

[y,Fs] = audioread('noisyaudio.wav');

Xk = fft(y);
X1 = fftshift(Xk);
x = linspace(-Fs/2,Fs/2,numel(y));

figure(1);
subplot(2,2,1), plot(x,abs(X1));
xlabel('Frequency (Hz)');
ylabel('Magnitude Spectrum');
title('DFT of Noisy Sound');

X1_normalized = 20*log10(X1/max(X1));

subplot(2,2,2), plot(x,X1_normalized);
ylim([-inf 0])
xlabel('Frequency (Hz)');
ylabel('Magnitude Spectrum');
title('Log Plot of DFT');

O = 0:0.05:pi; 
Ha = 20*log10(sqrt(1./(1+((O/1.5136).^(2*19)))));

subplot(2,2,3), plot(O, Ha);
xlabel('w');
ylabel('Gain dB');
title('Logarithmic Gain of Frequency Response');

h = 2655/(Fs/2);
[a,b] = butter(19,h);
y1 = filter(a,b,y);

Xk2 = fft(y1);
X2 = fftshift(Xk2);
x2 = linspace(-Fs/2,Fs/2,numel(y));

subplot(2,2,4), plot(x2,abs(X2));
xlabel('Frequency (Hz)');
ylabel('Magnitude Spectrum');
title('DFT for Filtered Sound');

%sound(y1);
audiowrite('filteredaudio.wav',y1,Fs);
