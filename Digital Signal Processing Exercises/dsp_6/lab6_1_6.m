clear all;
clc;
[B,A] = ellip(4, 0.25, 10, 0.25);
poles = roots(A);
zeroes = roots(B);

A1 = poly ([0.6715 + 0.7012i 0.6715 - 0.7012i]);
A1_two = twocomplement(A1/2);

A2 = poly ([0.4759 + 0.4613i 0.4759 - 0.4613i]);
A2_two = twocomplement(A2/2);

B1 = poly ([0.2697 + 0.9629i 0.2697 - 0.9629i]);
B1_two = twocomplement(B1/2);

B2 = poly ([0.6684 + 0.7438i 0.6684 - 0.7438i]);
B2_two = twocomplement(B2/2);

samples = zeros(1, 500);
samples(1) = 1;

A1_filter = filter(1,A1,samples);
G_A1 = (abs(sum(A1_filter)))^(-1);
G_A1_two = twocomplement(G_A1/2);

A2_filter = filter(1,A2,samples);
G_A2 = (abs(sum(A2_filter)))^(-1);
G_A2_two = twocomplement(G_A2/2);

B1_filter = filter(B1,1,samples);
G_B1 = (abs(sum(B1_filter)))^(-1);
G_B1_two = twocomplement(G_B1/2);

B2_filter = filter(B2,1,samples);
G_B2 = (abs(sum(B2_filter)))^(-1);
G_B2_two = twocomplement(G_B2/2);

G1 = G_A1 * G_B1;
G1_two = twocomplement(G1/2);

G2 = G_A2 * G_B2;
G2_two = twocomplement(G2/2);

filtro = fopen('filtro.h', 'w+');

fprintf(filtro, '#define A1_1 %d\n', A1_two(2));


fprintf(filtro, '#define A1_2 %d\n', A1_two(3));

fprintf(filtro, '#define A2_1 %d\n', A2_two(2));
fprintf(filtro, '#define A2_2 %d\n', A2_two(3));

fprintf(filtro, '#define B1_1 %d\n', B1_two(2));
fprintf(filtro, '#define B1_2 %d\n', B1_two(3));

fprintf(filtro, '#define B2_1 %d\n', B2_two(2));
fprintf(filtro, '#define B2_2 %d\n', B2_two(3));

fprintf(filtro, '#define G1_two %d\n', G1_two);
fprintf(filtro, '#define G2_two %d\n', G2_two);

fclose('all');



%% Filtro 4hs taxis 
clc;
clear;

[B,A] = ellip(4, 0.25, 10, 0.25);
A_two = twocomplement(A/4);
B_two = twocomplement(B/4);

samples = zeros(1, 500);
samples(1) = 1;

A_filter = filter(1,A,samples);
G_A = (abs(sum(A_filter)))^(-1);
G_A_two = twocomplement(G_A/4);

B_filter = filter(B,1,samples);
G_B = (abs(sum(B_filter)))^(-1);
G_B_two = twocomplement(G_B/4);

G = G_A * G_B;
G_two = twocomplement(G/4);

filtro = fopen('filtro4.h', 'w+');

fprintf(filtro, '#define A1 %d\n', A_two(2));
fprintf(filtro, '#define A2 %d\n', A_two(3));
fprintf(filtro, '#define A3 %d\n', A_two(4));
fprintf(filtro, '#define A4 %d\n', A_two(5));

fprintf(filtro, '#define B1 %d\n', B_two(2));
fprintf(filtro, '#define B2 %d\n', B_two(3));
fprintf(filtro, '#define B3 %d\n', B_two(4));
fprintf(filtro, '#define B4 %d\n', B_two(5));

fprintf(filtro, '#define G_two %d\n', G_two);

fclose('all');


