l1d = csvread('archive/gladman/1.csv');
l1d(l1d > 84) = 84;
l1d(l1d < 36) = 36;

%l1d = l1d(400000:end, :);



%heatmap(l1d(1000:00, :)');

%e_left = findchangepts(mean(l1d, 2), 'MaxNumChanges',2);
trace_means = mean(l1d, 2);

findchangepts(trace_means, 'MaxNumChanges',5);
% 

% 
line([1:numel(trace_means)], trace_means);

% 
% l1d = l1d(e_left:end, :);
% 
% set_means = mean(l1d, 1);
% 
% 
% eviction_m = zeros(size(l1d, 1), size(l1d, 2));
% 
% c = 1;
% for i = 1:size(l1d, 1)
%     for j = 1:size(l1d, 2)
%         eviction_m(c, j) = l1d(i, j) > set_means(j);
%     end
%     c = c + 1;
% end

%heatmap(eviction_m(1:2000, :)')


% grid off



 