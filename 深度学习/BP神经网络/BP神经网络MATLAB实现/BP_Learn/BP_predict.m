function [ output, Y ] = BP_predict( input, W, theta )
% ��ѵ���У���Ҫ��Ŀǰ��W��theta�Ƿ����Ҫ������жϡ�BP_predict��ר��Ϊ��ѵ��
%  ��д��Ԥ�⺯����ֻ�ܶԵ������ݣ�����ֵ�������м������Y
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

    