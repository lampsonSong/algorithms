
%
%
%   Date        :       2016-9-11
%   Author      :       lampson
%   Objective   :       Detect the concerntric circles and pick out points
%                       fastly
%   Input       :       Images from mobile
%   Output      :       dots:       the boundary pixels in outer circle
%                       i_dots:     the boundary pixels in inner circle
%   
%

clc;
clear;
clc;

tic;

img = imread('1.jpg');
figure;
imshow(img);

[h,w,~] = size(img);
im = rgb2gray(img);

    % illumination correction
    % http://cn.mathworks.com/help/images/examples/correcting-nonuniform-illumination.html
    se = strel('disk',200);
    se1 = strel('disk',50);
    fse = imdilate(im,se);
    background = imerode(fse,se1);
    I2 = background - im;
    im = imadjust(I2);


outer_im = im2bw(im);
inner_im = ~outer_im; 



% get boundaries and label regions
[B,L] = bwboundaries(outer_im, 'noholes');
S = regionprops(L,'MajorAxisLength','MinorAxisLength');

% test regions one by one
for i = 1:length(B)
           
        minor_R = S(i).MinorAxisLength;
        major_R = S(i).MajorAxisLength;

        % the region is not distorted too much
        diff2 = abs(major_R/minor_R - 1);
        % the region is not too small
        diff3 = major_R/max(h,w);
    
        
        if( diff2 < 2 && diff3 > 0.01)
                
               temp = B(i);
               dots = temp{1,1};

               hw = poly2mask(dots(:,2),dots(:,1),h,w);
               p_list = find(hw==1);
               area = length(p_list);

               if(area > 0)

               cir_L = bwlabeln(hw);
               cir_S = regionprops(cir_L,'MajorAxisLength','MinorAxisLength');
       
               min_R = cir_S.MinorAxisLength;
               maj_R = cir_S.MajorAxisLength;
               
               % the comparison between area and pixel numbers
               diff1 = abs(area/ (pi*(min_R/2)*(maj_R/2)) - 1);
              
                    if(diff1<0.01)
                       % inner circle detection
                       circle_im = zeros(h,w);
                       circle_im(p_list) = ~outer_im(p_list);

                       [i_B,i_L] = bwboundaries(circle_im, 'noholes');
                       i_S = regionprops(i_L,'Area','MajorAxisLength','MinorAxisLength');

                       len_S = length(i_S);

                       if(len_S > 1)
                           continue;
                       else           
                           for j=1:length(i_S)
                                i_area = i_S(j).Area;
                                i_minor_R = i_S(j).MinorAxisLength;
                                i_major_R = i_S(j).MajorAxisLength; 

                                i_diff1 = abs(i_area / (pi*(i_minor_R/2)*(i_major_R/2)) - 1);
                                i_diff2 = abs(i_major_R/i_minor_R - 1);
                                i_diff3 = i_major_R/max(h,w);

                                if(i_diff1 < 0.01 && i_diff2 < 2 && i_diff3 > 0.01)

                                    i_temp = i_B(j);
                                    i_dots = i_temp{1,1};

                                    hold on;
                                    plot(dots(:,2),dots(:,1),'g.');
                                    plot(i_dots(:,2),i_dots(:,1),'r.')
                                end
                           end
                       end
                       %end of inner circle detection
                    end
                end      
            
    
       end
end
    
    
toc;