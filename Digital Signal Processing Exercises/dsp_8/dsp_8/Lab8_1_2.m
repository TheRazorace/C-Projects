N = 256;% number of data points
M = 4096; % number of samples after zero padding 

t = 2*pi*1000*[0:N-1]'/8000;
x = sin(t); % generate samples of 1kHz sine with 8kHz sampling
x= x.*boxcar(N); % multiply by windowing function
x = [x; zeros(M-N,1)]; % zero padding 

s = abs(fft(x)).^2; % compute squared magnitude of FFT
s = s/max(s); % normalize so that max is 1.0
f = 8000*[0:M-1]/M; 

figure;
subplot(2,1,1);
plot(f(1:M/2),s(1:M/2));
xlabel('frequency (Hz)');
title('Squared FFT magnitude');
grid on;

subplot(2,1,2);
plot(f(M/8-31:M/8+31),s(M/8-31:M/8+31));
xlabel('frequency (Hz)');
title('Detailed view');
grid on;

