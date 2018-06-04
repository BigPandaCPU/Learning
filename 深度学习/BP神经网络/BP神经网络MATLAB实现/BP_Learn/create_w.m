function [ W ] = create_w( n_levels )
% 创建初始矩阵，初始值都是1.其中n_levels是一个向量

    n_level= numel( n_levels ) - 1;

    W = cell( n_level, 1 );

    for i = 1:n_level
        W{i} = ones( n_levels(i+1), n_levels(i) );
    end
end
