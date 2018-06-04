


   clc;
%{
c1 = [1 1];
c2 = [3 3];

n_L1 = 50; % number of item with label 1 
n_L2 = 20; % number of item with label 2
n_label = 1;

A = zeros(n_L1,3);
A(:,3) = 1;
B = zeros(n_L2,3);
B(:,3) = -1;

% create random point
for i=1:n_L1
    A(i,1:2) = c1 + rand(1,2);
end
for i=1:n_L2
    B(i,1:2) = c2 + rand(1,2);
end
% show points
scatter(A(:,1), A(:,2),[],'r');
hold on
scatter(B(:,1), B(:,2),[],'g');
X=[A;B];
clc
%}

%% ---- Build a training set of a similar version of XOR

c_1 = [0 0];
c_2 = [1 1];
c_3 = [0 1];
c_4 = [1 0];

n_L1 = 20; % number of label 1
n_L2 = 20; % number of label 2


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



%% Trainning the BP network
dbstop if error
n_label = 1;
% create the weight matrix
n_input = size(X,2) - n_label;% number of feature of each data, here is 2, only x-axis and y-axis
levels = [n_input 1 1];

step = 1;

[W,theta] = BP_tranning(X, levels, step);
save two_class W theta

%% test
input = X(:,1:2);
label = X(:,3:end);
y = BP_predict2(input, W, theta);
Y = y';
Y(find(Y>0.5)) = 1;
Y(find(Y<=0.5)) = 0;

A = W{1}(1);
B = W{1}(2);
C = theta{1}(1);
if B==0
    %生成100个-C/A放在向量x中.
    x=linspace(-C/A,-C/A,100);
    %从-A)-(|A|+|B|+|C|)到|A|+|B|+|C|等距离生成100个值放在向量y中.?
    y=linspace(-abs(A)-abs(B)-abs(C),abs(A)+abs(B)+abs(C),100);
else
    x = linspace(0, 10, 100);
    y = -A/B * x;
    y = y - 1/B*C;
end
hold on
plot(x,y)