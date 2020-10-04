N = 64;
Fs = 48000;
f = 10000;

t = 2*pi*f*[0:N-1]'/Fs;
x = sin(t); % generate samples of 10kHz sine with 48kHz sampling   
x = twocomplement(x/2);

sin_samples = fopen('sin_samples.h', 'w+');
fprintf(sin_samples, 'short sin_samples[64] = {\n');
for i=1:64
    fprintf(sin_samples, '%d,\n', x(i));
end
fprintf(sin_samples, '}\n');

fclose('all');