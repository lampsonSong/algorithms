%
%
%
%       Date        :       2016-10-31
%       Author      :       lampson
%       Objective   :       Discrete Cosine Transform
%       Input       :       1-D, 2-D data
%       Output      :       DCT coefficients
%
%
%


function coe = myDCT(input_data)

[n,m] = size(input_data);

coe = double( zeros(n,m) );


for y = 1:m
   row_ww = cos( (2*(0:m-1)+1)*(y-1)*pi/(2*m) );
    
   if(y==1)
       cv = sqrt(1/m);
   else
       cv = sqrt(2/m);
   end
   
    for x = 1:n
        col_ww = cos( (2*(0:n-1)+1)*(x-1)*pi/(2*n) );

       if(x==1)
           cu = sqrt(1/n);
       else
           cu = sqrt(2/n);
       end
       
       
       coe(x,y) = cu*cv * row_ww*(col_ww*input_data)';
    end
end

end


%
%
%       This algorithm is okay, but the running speed is very slow
%       The better solution is to use 1D DCT for 2D, and 1D DCT using FFT
%
%
