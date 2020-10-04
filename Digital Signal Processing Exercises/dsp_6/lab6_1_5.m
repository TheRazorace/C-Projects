[B,A] = ellip(4, 0.25, 10, 0.25);
figure(1);
freqz(B,A);
poles = roots(A);
zeros = roots(B);

A1 = poly ([0.6715 + 0.7012i 0.6715 - 0.7012i]);
A2 = poly ([0.4759 + 0.4613i 0.4759 - 0.4613i]);
B1 = poly ([0.2697 + 0.9629i 0.2697 - 0.9629i]);
B2 = poly ([0.6684 + 0.7438i 0.6684 - 0.7438i]);

figure(2);
freqz(B1,A1);
figure(3);
freqz(B2,A2);