function [ W ] = create_w( n_levels )
% ������ʼ���󣬳�ʼֵ����1.����n_levels��һ������

    n_level= numel( n_levels ) - 1;

    W = cell( n_level, 1 );

    for i = 1:n_level
        W{i} = ones( n_levels(i+1), n_levels(i) );
    end
end
