function [ theta ] = create_theta( levels )
% ����ƫ�������󣬳�ʼֵ����1
    n_level = numel(levels) - 1;
    theta = cell( n_level, 1 );
    
    for i = 1:n_level
        theta{i} = ones( levels(i+1), 1);
    end
end
