function [ varargout ] = dealx( v )
% assigns the elements of a vector v to a list of varibales,
% e.g. r=[1 2 3]; [x,y,z] = dealx(r);
    L = length(v);
    if nargout < L
        warning('Ignoring extra elements in vector for assignment.');
    end
    if nargout > L
        error('Vector as not enough elements for assignment.');
    end
    for k=1:nargout
        varargout{k} = v(k);
    end
end
