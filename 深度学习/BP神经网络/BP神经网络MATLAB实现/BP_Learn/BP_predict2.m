function [ output ] = BP_predict2( input, W, theta )
% BP_predict2用于预测，可以对一个数据矩阵进行预测

    f = @sigmoid;
    n_w = numel(W);
    
    y = input';
    for i =1:n_w
        net = bsxfun( @plus, W{i}*y, theta{i} );
        y = f(net);
    end;
    output = y;
end

    