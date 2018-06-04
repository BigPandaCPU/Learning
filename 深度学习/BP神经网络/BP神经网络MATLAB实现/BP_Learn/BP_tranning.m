function [ W, theta ] = BP_tranning( X, levels, step ,maxStep)
    
    if nargin < 3
        step = 0.001;
        maxStep = 10000;
    end
    if nargin < 4
        maxStep = 10000;
    end
    
    n_levels = size( levels, 2 ) - 1;
    n_input  = levels(1);
    
    W = create_w( levels );
    theta = create_theta( levels );
    
    [ n_data, col] = size( X );
    n_label = col - n_input; %% 这里是啥意思呢？
    
    trainning_data = X( :, 1:n_input);  %%Y0 is input
    label = X(:, n_input+1:end)';
    
    f = @sigmoid;
    eps = 10e-7; 
    old_error = 0;
    stepTime = 0;
    while stepTime < maxStep
        for k = 1:n_data
            [ output, Y ] = BP_predict( trainning_data(k,:), W, theta );
            delta = label(:,k) - output;
            
            for l = n_levels:-1:1
                net = W{l}*Y{l} + theta{l};
                if l == n_levels
                    S = diag( f(net).*( 1 - f(net) ) ) * delta;
                else
                    S = diag( (f(net).*( 1 - f(net) )) ) *W{l+1}' * S;
                end
                %dW = -S*Y{l}
                  new_W{l} = W{l} + step * S * Y{l}';
                new_theta{l} = theta{l} + step * S;
            end
            
            W = new_W;
            theta = new_theta;
        end
        
        y = BP_predict2( trainning_data, W, theta );
        delta = y - label;
        error = sum( sum( delta.^2) );
        if( abs( error - old_error ) < eps )
            break;
        else
            old_error = error;
        end
        stepTime = stepTime +1;
        if ( mod(stepTime, 10000) == 0 )
            W{1}
            W{2}
            theta{1}
            theta{2}
        end
            
    end
end

            
                
                
                
                
    
    
