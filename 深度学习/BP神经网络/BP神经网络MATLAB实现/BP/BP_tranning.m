function [ W,theta ] = BP_tranning( X, levels, step )
%BP_TRANNING Summary of this function goes here
%   Detailed explanation goes here
    if nargin < 3
       step = 0.01; 
    end
    
    n_levels = size(levels, 2) - 1;
    n_input = levels(1);
    W = create_w(levels);
    theta = create_theta(levels);
    
    [n_data,col] = size(X);
    n_label = col - n_input;
    
    tranning_data = X(:,1:n_input); %Y0 is input
    label = X(:,n_input+1:end)';
    f = @sigmoid;
    
    eps = 10e-5;
    old_error = 0;
    while true

        for k=1:n_data
           [output, Y] =  BP_predict(tranning_data(k,:), W, theta);
           delta = label(:,k) - output;
           % update the W, from the last layer to the first layer
           for l=n_levels:-1:1
              net = W{l}*Y{l} + theta{l};
              if l == n_levels
                  S = diag(f(net).*(1-f(net)))*delta;
              else
                  S = diag((f(net).*(1-f(net))))*W{l+1}'*S;
              end
              %dW = -S*Y{l}';
              new_W{l} = W{l} + step*S*Y{l}';
              new_theta{l} = theta{l} + step*S;
           end % end update
           W = new_W;
           theta = new_theta;
           
            
        end % end for
        
        y = BP_predict2(tranning_data, W, theta);
        delta = y - label;
        error = sum(sum(delta.^2))
        if abs(error - old_error) < eps;
            break;
        else
            old_error = error;
        end

    end
end

