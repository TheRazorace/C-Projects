function Y = Goertzel(x,coef)
    Qn_1 = 0;
    Qn_2 = 0;
    N = 205;
    for l = 1:N
        Q_n = x(l)+ coef *Qn_1 - Qn_2;           %% Q[n] = x[n] + 2cos[2ðn/N]Q[n-1] - Q[n-2]
        Qn_2 = Qn_1;
        Qn_1 = Q_n;
        t = coef*Qn_1
    end
    Y = Q_n^2 + Qn_1^2 - coef * Q_n * Qn_1;   %% |y[n]|^2 = Q[N]^2 + Q[N-1]^2 - 2cos[2ðn/N]Q[N]Q[N-1]
end