clear, clc;
SerialPort='COM3';
TimeInterval=0.2;

port = serialport('COM3', 115200);
% XYZ = [0.5273, -0.0346, 0.0980, 0.5062, 0.0001, 0.1199, 0.4191, 0.0646, 0.1719, 0.3863, 0.2579, 0.0636];
XYZ = [5, 20, 10, 30];
write(port, 1, 'uint8');
disp 'Start'
write(port, XYZ, 'single');

time = now;

figureHandle = figure('NumberTitle','off',...
    'Name','Angle',...
    'Color',[0 0 0],'Visible','off');

% Set axes
axesHandle = axes('Parent',figureHandle,...
    'YGrid','on',...
    'YColor',[0.9725 0.9725 0.9725],...
    'XGrid','on',...
    'XColor',[0.9725 0.9725 0.9725],...
    'Color',[0 0 0]);

hold on;
% angle(1,1:3)=[0, 0, 0];
angle(1)=0;
plotHandle1 = plot(axesHandle,time,angle,'Marker','.','LineWidth',1,'Color',[0 1 0]);

xlim(axesHandle,[min(time) max(time+0.001)]);

% a = [0, 0, 0];
a = 0;
% angle(1,1:3)=[0, 0, 0];
angle(1)=0;
time(1)=0;
count = 2;
k=1;

while 1
    
%     a = read(port, 3, 'single');
    a = read(port, 1, 'single');

%     if ((a(1) == 300)&&(a(2) == 300)&&(a(3) == 300))
%     if (a == 300)
    if isempty(a)
%         a = [0,0,0];
        a = 0;
        break;
    end
%     angle(count,1:3) = a;
%     angle(count) = a(1);
    angle(count) = a;
     
    time(count) = count;
%     set(plotHandle1,'YData',angle(count,1:3),'XData',time);
    set(plotHandle1,'YData',angle,'XData',time);
    set(figureHandle,'Visible','on');
    datetick('x','mm/DD HH:MM');
    pause(TimeInterval);
    count = count + 1;
end

clear port;