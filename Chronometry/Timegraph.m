[y, Fs] = audioread('clock.mp3');
y = 0.5*(y(:,1)+y(:,2));
first = 1;
dur = 0.1;
step_size = dur * Fs;
last = step_size;
peak_loc = [];
while (last + step_size < length(y))
    [env_upper, env_lower] = envelope(y(first:last), Fs/100, 'rms');
    [pk, loc] = max(env_upper);
    if (pk > 0.001)
        peak_loc =[peak_loc (first-1)+loc];
    end
    first = first + step_size;
    last = last+ step_size;
end
diff = zeros(1, length(peak_loc)-1);
j = 2;

for i = 1:length(diff)
    diff(i)= peak_loc(j) - peak_loc(j-1);
    j = j+1;
end

k = 3;
diff2 = zeros(1, length(peak_loc)-2);

for i=1:length(diff2)
    diff2(i) = peak_loc(k) - peak_loc(k-2);
    k = k+1;
end

rate = zeros(1, length(diff2)-1);
j=1;
for i = 1:length(rate)
    rate(i) = ((diff2(j) + diff2(j+1))/(2*Fs));
    j = j+1;
end

frequency = Fs./(diff2);

average = mean(rate);
dev = average - rate;

integration_time = 2;
no_samples = integration_time / average;

beat_error = zeros(1, length(diff)-1);
j = 2;
for i = 1:length(beat_error)
     beat_error(i) = (diff(j) - diff(j-1))/(2*Fs);
     j = j+1;
end

average_dev = [];
average_beat_error = [];
average_frequency = [];
first2 = 1;
step_size2 = round(no_samples);
last2 = step_size2;

while ((last2 + step_size2)<length(dev))
    avg_dev = mean(dev(first2:last2));
    avg_beat_error = mean(beat_error(first2:last2));
    avg_frequency = mean(frequency(first2:last2));
    average_dev = [average_dev avg_dev];
    average_beat_error = [average_beat_error avg_beat_error];
    average_frequency = [average_frequency avg_frequency];
    first2 = first2 + step_size2;
    last2 = last2 + step_size2;
end
t1 = 0:length(envelope(average_dev,1,'peak'))-1;
t2 = 0:length(envelope(average_beat_error, 1, 'peak'))-1;
t3 = 0:length(average_frequency)-1;
figure;
plot(t1, envelope(average_dev,1,'peak'));
xlabel('time (sec)');
ylabel('deviation (sec)');
title('deviation rate');
figure;
xlswrite('deviation rate.csv',envelope(average_dev,1,'peak'))

plot(t2, envelope(average_beat_error, 1, 'peak'));
xlabel('time (sec)');
ylabel('beat_error (sec)');
title('beat error');
figure;
xlswrite('deviation rate.csv',envelope(average_beat_error,1,'peak'))

plot(t3, average_frequency);
xlabel('time (sec)');
ylabel('frequency');
title('Beat frequency');
xlswrite('Beat frequency.csv',envelope(average_frequency,1,'peak'))

