function showKeypoints(cams, justPts, idxs, subfigX, subfigY)
        
if ~exist('subfigX','var')
    subfigX = 4;
end
if ~exist('subfigY','var')
    subfigY = 3;
end

nCams = numel(cams);

if ~exist('idxs','var')
    idxs=1:nCams;
end

subFigIdx = 1;
for i=idxs
    
    img = imread(cams(i).fn);
    subfig(subfigY, subfigX, mod(subFigIdx-1,subfigX*subfigY) + 1);
    subFigIdx = subFigIdx+1;
    
    hold on;
    image(img);
    axis ij
    axis equal;
    axis tight
    
%     s=cell2mat({cams(i).keys(:).scale});
%     keys = cams(i).keys(s>5);
%     plotKeys(keys, justPts);
%     plotKeys(cams(i).keys, justPts);
    
    title(['img: ', num2str(i), ' # keys: ', num2str(numel(cams(i).keys))]);
    hold off
    drawnow
    
    axis off
%     title('');
%     set(gca, 'Color', 'none');
%     addpath export_fig
%     fn = sprintf('keys-%i.pdf',i);
%     fn = fullfile('C:\Users\Filip\Dropbox\Diplomka\cmpthesis\imgs',fn);
%     export_fig(fn,'-native','-transparent');
    
end

end