clear all;
clc;

[B,A] = butter(2,[0.07 0.10],'stop')
poles1 = roots(A)
zeroes1 = roots(B)
figure(1)
freqz(B,A);

B = 8*((round((B*32768/8)))/32768)
A = 8*((round((A*32768/8)))/32768)
poles2 = roots(A)
zeroes2 = roots(B)
figure(2)
freqz(B,A);


%%

clear all;
clc;

[B,A] = butter(2,[0.07 0.10],'stop')
poles1 = roots(A);
zeroes1 = roots(B);
figure(1)
freqz(B,A);


A1 = poly ([ 0.9461 + 0.2378i 0.9461 - 0.2378i]);
A2 = poly ([0.9208 + 0.2679i  0.9208 - 0.2679i]);
B1 = poly ([0.9628 + 0.2701i  0.9628 - 0.2701i]);
B2 = poly ([0.9684 + 0.2494i  0.9684 - 0.2494i]);

B1 = 8*((round((B1*32768/8)))/32768);
A1 = 8*((round((A1*32768/8)))/32768);

B2 = 8*((round((B2*32768/8)))/32768);
A2 = 8*((round((A2*32768/8)))/32768);



figure(2);
freqz(B1,A1)
figure(3);
freqz(B2,A2)



%%

clc;
clear;
[B1,A1] = butter(1,[0.07 0.10],'stop')
[B2,A2] = butter(1,[0.07 0.10],'stop')

B1 = 8*((round((B1*32768/8)))/32768)
A1 = 8*((round((A1*32768/8)))/32768)

B2 = 8*((round((B2*32768/8)))/32768)
A2 = 8*((round((A2*32768/8)))/32768)


H1=dfilt.df2t(B1,A1);
H2=dfilt.df2t(B2,A2);


Hcas=dfilt.cascade(H1,H2)

freqz(Hcas);
phasez(Hcas);