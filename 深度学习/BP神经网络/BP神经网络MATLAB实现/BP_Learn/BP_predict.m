function [ output, Y ] = BP_predict( input, W, theta )
% 在训练中，需要对目前的W和theta是否符合要求进行判断。BP_predict是专门为了训练
%  而写的预测函数，只能对单个数据，返回值包括了中间层的输出Y
    f = @sigmoid;
    n_w = numel( W );
    Y = cell( n_w + 1, 1 );
    Y{ 1 } = input';
    
    for i = 1:n_w
        net = W{i} * Y{i} + theta{i};
        Y{ i+1 } = f(net);
    end
    output = Y{end};
end

    