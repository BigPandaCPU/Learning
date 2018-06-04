clc

%% ---- Build a training set of a similar version of XOR
%{
c_1 = [0 0];
c_2 = [1 1];
c_3 = [0 1];
c_4 = [1 0];

n_L1 = 20; % number of label 1
n_L2 = 20; % number of label 2
n_label = 1;

A = zeros(n_L1*2, 3);
A(:,3) = 1;
B = zeros(n_L2*2, 3);
B(:,3) = 0;

% create random points
for i=1:n_L1
   A(i, 1:2) = c_1 + rand(1,2)/2;
   A(i+n_L1, 1:2) = c_2 + rand(1,2)/2;
end
for i=1:n_L2
   B(i, 1:2) = c_3 + rand(1,2)/2;
   B(i+n_L2, 1:2) = c_4 + rand(1,2)/2;
end

% show points
scatter(A(:,1), A(:,2),[],'r');
hold on
scatter(B(:,1), B(:,2),[],'g');

X = [A;B];
%}










