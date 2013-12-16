function p191
% state vectors: [state, L allowed, (opt) A allowed]
% 7 states:
% 1: [O, 1]
% 2: [O, 0]
% 3: [L, 0]
% 4: [A, 1, 1]
% 5: [A, 0, 1]
% 6: [A, 1, 0]
% 7: [A, 0, 0]

% allowed transitions:
% 1 -> {1, 3, 4}
% 2 -> {2, 5}
% 3 -> {2, 5}
% 4 -> {1, 3, 6}
% 5 -> {2, 7}
% 6 -> {1, 3}
% 7 -> {2}

tic;
N = 30;

x = [1 0 1 1 0 0 0]';
% store transition matrix
Q = [ [1 0 1 1 0 0 0];...
 [0 1 0 0 1 0 0];...
 [0 1 0 0 1 0 0];...
 [1 0 1 0 0 1 0];...
 [0 1 0 0 0 0 1];...
 [1 0 1 0 0 0 0];...
 [0 1 0 0 0 0 0] ]';

Ans = sum(Q^(N-1)*x);
fprintf('Computation done in %gs\n', toc);
fprintf('Number of allowed sequences: %.15g\n', Ans);
