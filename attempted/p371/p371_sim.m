n = 10000;

X = 200;

rand_ints = floor(rand(X,n) * 1000);

sum = 0;
for i = 1:n,
    hits = zeros(1000,1);
    j = 0;
    stop = 0;
    while stop == 0,
        j = j + 1;
        h = rand_ints(j, i);
        if h ~= 0,
            target = 1000-h;
            if hits(target+1) == 1,
                stop = 1;
            end;
        end;
        hits(h + 1) = 1;
    end;
    sum = sum + j;
    fprintf("hit after j == %d\n", j);
end;

fprintf("mean time: %f\n", sum / n);
