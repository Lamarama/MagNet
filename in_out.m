%Finds position of puck magnet with a quadratic approxmiation of puck field
function in_out
Bpuck=[-0.0977 0.1215 -0.0011]; %quadratic approximation of puck field
c;    % constant quantifying the relation between Voltage input and corresponging B 
c2;   %constant quantifying relationship between input to solenoids 'u' and the resulting B
yd=0; %Desired position
rpos=0; % current position of puck 
e=0;    %error (offset from desired position)
A;B;C:D; % matricies for control calculation

%Define x for control calculations
persistent x  
if isempty(x)
    x=[0;0;0;0;];
end

%define u for input to solenoids
persistent u
if isempty(u)
    u=0;
end

%///////Insert line to read in input "i" from hall sensors ////////%


B=i*c;  %finds B based on relationship of sensor input "i" to B
Bs=u*c2; %finds B from solenoids based on the present output level 'u' of solenoid;

pos=roots([ Bpuck(1) Bpuck(2) Bpuck(3)-B-Bs ]);

%now have two possible x positions that could correspond to the puck's
%position. Have to choose smaller x (since we're looking at the left side
%of a negative quadratic)

if pos(1)<pos(2)
    rpos=pos(1);
else
   rpos=pos(2);
end

e=(yd-rpos); %obtains the error (present offset from desired position)

u=C*x+D*e;
x=A*x+B*e;


end