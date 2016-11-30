%
%
%       Date        :       2016-11-9
%       Author      :       lampson
%       Objective   :       An implementation of DFT for images, just as
%                           equation, no optimization
%
%
%


function coe = myDFT(data)

% data = [1 2 3 4 5; 6 7 8 9 20];

[w,h] = size(data);

coe = zeros(w,h);

x = 0:1:w-1;
y = 0:1:h-1;

for col_ind = 0:h-1
    row_ww = exp(-2*pi*i*(y*col_ind)/h);
    for row_ind = 0:w-1
        col_ww = exp(-2*pi*i*(x*row_ind)/w)
        
        coe(row_ind+1,col_ind+1) = row_ww*(col_ww*data)';
    end
end

end


%
%   Just an implementation according to the equation, no optimization
%