%%% test my bp network

c_1 = [0,0];
c_2 = [0,1];
c_3 = [1,0];
c_4 = [1,1];

n_L1 = 20;
n_L2 = 20;
n_L3 = 20;
n_L4 = 20;

A = zeros( n_L1, 4 );
A(:,3) = 0;
A(:,4) = 0;

for i = 1:n_L1
    A( i, 1:2 ) = c_1 + rand(1,2)/2;
end

B = zeros( n_L2, 4 );
B(:,3) = 0;
B(:,4) = 1;
for i = 1:n_L2
    B(i,1:2) = c_2 + rand(1,2)/2;
end

C = zeros( n_L3, 4 );
C(:,3) = 1;
C(:,4) = 0;
for i = 1:n_L3
    C(i, 1:2) = c_3 + rand(1,2)/2;
end

D = zeros( n_L3, 4 );
D(:,3) = 1;
D(:,4) = 1;
for i = 1:n_L4
    D(i, 1:2) = c_4 + rand(1,2)/2;
end

scatter( A(:,1), A(:,2), [], 'r');
hold on
scatter( B(:,1), B(:,2), [], 'g');
scatter( C(:,1), C(:,2), [], 'k');
scatter( D(:,1), D(:,2), [], 'y');

X = [A;B;C;D];

dbstop if error
n_label = 2;
%create the weight matrix
n_input = size(X,2) - n_label;
levels = [n_input 8 n_label]; 
%{
n_input：表示输入的神经元个数
8：表示隐含层神经元个数
n_label：表示输出层的神经元个数
%}
step = 0.01;
[ W, theta ] = BP_tranning( X, levels, step ,50000);
save three_class W theta

input = X(:, 1:n_input);
label = X(:, n_input+1:end);
y = BP_predict2( input, W, theta );
Y = y';
Y( find( Y >  0.5) ) = 1;
Y( find( Y <= 0.5) ) = 0;
T = sum( label - Y, 2 );
error_index = find( T~= 0 );
figure
scatter( X(:,1), X(:,2), [],'g');
hold on
scatter(X(error_index,1), X(error_index,2), [], 'r');





