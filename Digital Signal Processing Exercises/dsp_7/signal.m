function f = signal(x)
    Fs = 8000;
    N = 205;
    f = sin(2*pi*x*(1:N)/Fs);
end