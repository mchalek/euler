function p213
tic;
% First generate transition matrix.
P = zeros(900);
for i = 1:30
    for j = 1:30
        if i == 1 && j == 1 % top left corner
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 0.5;
            P(i + j*30, i + (j-1)*30) = 0.5;
        elseif i == 30 && j == 1 % bottom left corner
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 0.5;
            P(i + j*30, i + (j-1)*30) = 0.5;
        elseif i == 1 && j == 30 % top right corner
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 0.5;
            P(i + (j-2)*30, i + (j-1)*30) = 0.5;
        elseif i == 30 && j == 30 % bottom right corner
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 0.5;
            P(i + (j-2)*30, i + (j-1)*30) = 0.5;
        elseif i == 1 % top edge
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + (j-2)*30, i + (j-1)*30) = 1/3;
            P(i + j*30, i + (j-1)*30) = 1/3;
        elseif i == 30 % bottom edge
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + (j-2)*30, i + (j-1)*30) = 1/3;
            P(i + j*30, i + (j-1)*30) = 1/3;
        elseif j == 1 % left edge
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + j*30, i + (j-1)*30) = 1/3;
        elseif j == 30 % right edge
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 1/3;
            P(i + (j-2)*30, i + (j-1)*30) = 1/3;        
        else % internal
            P(i - 1 + (j-1)*30, i + (j-1)*30) = 0.25;
            P(i + 1 + (j-1)*30, i + (j-1)*30) = 0.25;
            P(i + j*30, i + (j-1)*30) = 0.25;
            P(i + (j-2)*30, i + (j-1)*30) = 0.25;
        end;
    end;
end;
P = sparse(P);
P50 = P^50;
fprintf('Expected number of empty: %.10g\n', sum(prod(1-P50,2)));
toc