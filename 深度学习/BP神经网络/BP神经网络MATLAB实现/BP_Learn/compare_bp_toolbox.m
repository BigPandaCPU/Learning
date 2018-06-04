clear;
clc;

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

P=X(:,1:2);
T=X(:,3:4);
%利用minmax函数求输入样本范围
[Pn, input_str]  = mapminmax(P);
[Tn, output_str] = mapminmax(T); 
net = newff(Pn,Tn,[2,10,2],{'purelin','logsig','purelin'});

net.trainParam.show=50;  %显示训练迭代过程
net.trainParam.lr=0.001;  %学习率
net.trainParam.epochs=50000; %最大训练次数
net.trainParam.goal=1e-5; %训练要求精度
[net,tr]=train(net,P,T); %网络训练

W1= net.iw{1, 1}  %输入层到中间层的权值
B1 = net.b{1} %中间各层神经元阈值
W2 = net.lw{2, 1} %中间层到输出层的权值
B2 = net.b{2} %输出层各神经元阈值

T_temp    = sim(net,P) %利用得到的神经网络仿真
T_predict = mapminmax('reverse', T_temp, output_str);
Y = T_predict;

Y( find( Y >  0.5) ) = 1;
Y( find( Y <= 0.5) ) = 0;
error = sum( T - Y, 2 );
error_index = find( error~= 0 );
figure
scatter( X(:,1), X(:,2), [],'g');
hold on
scatter(X(error_index,1), X(error_index,2), [], 'r');
