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
%����minmax����������������Χ
[Pn, input_str]  = mapminmax(P);
[Tn, output_str] = mapminmax(T); 
net = newff(Pn,Tn,[2,10,2],{'purelin','logsig','purelin'});

net.trainParam.show=50;  %��ʾѵ����������
net.trainParam.lr=0.001;  %ѧϰ��
net.trainParam.epochs=50000; %���ѵ������
net.trainParam.goal=1e-5; %ѵ��Ҫ�󾫶�
[net,tr]=train(net,P,T); %����ѵ��

W1= net.iw{1, 1}  %����㵽�м���Ȩֵ
B1 = net.b{1} %�м������Ԫ��ֵ
W2 = net.lw{2, 1} %�м�㵽������Ȩֵ
B2 = net.b{2} %��������Ԫ��ֵ

T_temp    = sim(net,P) %���õõ������������
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
