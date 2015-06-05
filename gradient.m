img = imread('input.jpeg');

mysize = size(img);

%whether it is a gray image
if numel(mysize) > 2
    img = rgb2gray(img);
end

[width,height] = size(img);
img = double(img);

% X-gradient image and Y-gradient image
img_x = zeros(width,height);
img_y = zeros(width,height);


filter = [-1;1];


for i = 1:width
    for j = 1:height
        if i + 1 < width
           img_x(i,j) = [img(i,j) img(i+1,j)] * filter; 
        else
            img_x(i,j) = img(i,j);
        end
        
        %y graident image
        if j+1 < height
            img_y(i,j) = [img(i,j) img(i,j+1)] * filter;
        else
            img_y(i,j) = img(i,j);
        end
    end
end

img = uint8(img);
img_x = uint8(img_x);
img_y = uint8(img_y);

imshow(img);
figure;
imshow(img_x);
figure;
imshow(img_y);