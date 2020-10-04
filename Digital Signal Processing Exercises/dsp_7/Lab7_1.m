
f_lo = [697 770 852 941];
f_hi = [1209 1336 1477 1633];

spectrum_lo=[0 0 0 0];
spectrum_hi=[0 0 0 0];

coef_lo = [1.703275 1.635585 1.562297 1.482867];
coef_hi = [1.163138 1.008835 0.790074 0.559454];

buttons = ['1','2','3','A' ; '4','5','6','B' ; '7','8','9','C' ; '*','0','#','D'];

for i=1:4
    for j=1:4
        data = signal(f_lo(i)) + signal(f_hi(j));
        
        for k=1:4
            spectrum_lo(k) = Goertzel(data, coef_lo(k));
            spectrum_hi(k) = Goertzel(data, coef_hi(k));
        end
        
        [freq1, low] = max(spectrum_lo);
        [freq2, high]= max(spectrum_hi);
        fprintf(('   %c'),buttons(low, high));
        
        if j==4
            fprintf('\n');
        end
    end
end





