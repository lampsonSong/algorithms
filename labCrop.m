% Date: 2015-11-4
% Input: an image
% Output: segmented obejct

% apply the segmentation in CIE-LAB color space

clc;
clear;
clc;

original_I= imread('bay2.jpg');

[h,w,dim] = size(original_I); 

I_M = reshape(original_I,h*w,dim);
rgbM = zeros(h*w,dim);

cform = makecform('srgb2lab');
lab_I = applycform(original_I,cform);
lab_M = double( reshape(lab_I,h*w,dim) );

lab_color = lab_M(:,2:3);
% show original image
figure(1);
imshow(original_I);
 
% get 5 object color and bg color && object position

target_color = zeros(6,3);
target_pos = zeros(6,2);

for i = 1:6
    h1 = imrect;
    region = getPosition(h1);
    
    c_img = imcrop(lab_I,region);
    [cw,ch,dim] = size(c_img);
    
    regionImg = reshape(c_img,cw*ch,dim);
    target_color(i,:) = mean(regionImg);
    
    x = double(region(1) + region(3)/2);
    y = double(region(2) + region(4)/2);
    target_pos(i,:) = [x y];
end
%object and bg color
object_color = mean(target_color(1:5,:));
bg_color = target_color(6,2:3);

close(figure(1));

% initilize coordinates for image pixels
coord_x = ones(h,w);
coord_y = ones(h,w);

rows = ones(1,w);
for i=2:h
    coord_y(i,:) = coord_y(i,:) + (i-1)*rows;
end
columns = ones(h,1);
for i = 2:w
   coord_x(:,i) = coord_x(:,i) + (i-1)*columns; 
end

index = [];
% compute the coordinate region
for coord_i = 1:5
        t_color = double( target_color(coord_i,2:3) );
        x = target_pos(coord_i,1);
        y = target_pos(coord_i,2);

        coord_dist = (coord_x - repmat(x,h,w)).^2 + (coord_y - repmat(y,h,w)).^2;
        coord_dist = reshape(coord_dist,h*w,1);
        coord_dist = ceil(coord_dist);

        %dist = color_dist + coord_dist;
        %dist = coord_dist;

        max_coord = max(coord_dist);
        min_coord = min(coord_dist);
        threshold = double((max_coord+min_coord)/30);
        ind = find(coord_dist < threshold);
        
        %
        % color region
        %
        [num,~] = size(ind);

        color_diff = lab_color(ind,:) - repmat(t_color,num,1);
        %bg_diff = lab_color(ind,:) - repmat(bg_color,num,1);

        color_dist = sum( color_diff.^2,2 );
        color_dist = ceil(color_dist);
        max_color = max(color_dist);
        %bg_dist = sum( bg_diff.^2,2 );

        dist = (coord_dist(ind)/max_coord)*1000 + (color_dist/max_color)*100;
        dist = ceil(dist);

        %ind_out = find( color_diff > 0 );
        color_ind = find( dist < 30 );
        l_ind = ind(color_ind);
        [l_num,~] = size(l_ind);
        
        %compute the l channel distance
        l_diff = lab_M(l_ind,1) - repmat( target_color(coord_i,1),l_num,1 );
        l_dist = l_diff.^2;
        
        ind_out = find(l_dist < 4000);
        
        index = [index;l_ind(ind_out)];
        ind_out = [];
        l_ind = [];
        ind = [];
end


%rgbM(ind_out,:) = I_M(ind_out,:);
rgbM(index,:) = I_M(index,:);
out = reshape(rgbM,h,w,dim);
img = uint8(out);
imshow(img);