load_vector('bufferright.dat');

Y = fft(ans);
Fs = 48000;           % Sampling frequency                    
T = 1/Fs;             % Sampling period       
L = 1024;             % Length of signal
t = (0:L-1)*T;        % Time vector

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;
plot(f,P1) 
title('White Noise Spectrum')
xlabel('f (Hz)')
ylabel('|P1(f)|')