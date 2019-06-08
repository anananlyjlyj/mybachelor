%% square periodic function

G=1;                % spacing in momentum space = 2*pi/Periode - aperiodisch -> G = 0 

N=80;              % maximum momentum/maximum k-vector
n = (-N:N)+eps;     % vector describing momentem space axis; for multiples of G; eps - such that there is no devision by zero 
    
x=-80:0.01:80;      % vector describing real space axis

Psi = x*0;g_n =[];  % initialization 


% \Psi periodic square pattern = wave function after diffraction gratings
duty = 0.1;                         % ratio width to period
g_n = 1./n/pi.*sin(n*pi*duty);      % corresponding momentum distribution = fourier transform 

figure(1)
stem((-N:N)*G,g_n)
axis([-80,80, -0.05, 0.15])
title('Impulsraum/Amplituden der deBroglie Wellen')
xlabel('k [2*\pi/d]')
disp('the de Broglie waves we are going to use')
y_max = 0.15;  % for the proper display

%% gaussian wave packet



G=1;                % spacing in momentum space = 2*pi/Periode - aperiodisch -> G = 0 

N=80;              % maximum momentum/maximum k-vector
n = (-N:N)+eps;     % vector describing momentem space axis; for multiples of G; eps - such that there is no devision by zero 
    
x=-80:0.01:80;      % vector describing real space axis

Psi = x*0;g_n =[];  % initialization 


% \Psi gaussian = wave function after diffraction gratings
duty = 0.1;                         % ratio width to period
g_n = exp(-n.^2/15^2);      % corresponding momentum distribution = fourier transform 

figure(1)
stem((-N:N)*G,g_n)
axis([-80,80, -0.05, 1.1])
title('Impulsraum/Amplituden der deBroglie Wellen')
xlabel('k [2*\pi/d]')
disp('the de Broglie waves we are going to use')

y_max = 1.15;  % for the proper display




%%

% only few deBroglie waves = \Psi \propto cos(Gx) 
G = 1;   % 5  or 0.6
Psi = 0*x;
select = [-1 1];  
%select = [-1 0 1];
%select = -5:5;
select = -N:N;

for cntr = select, 
    Psi = Psi + g_n(N+1+cntr)*exp(i*n(N+1+cntr)*G*x); 
 end;

figure(2)
stem(n*G,g_n,'b'); hold on; stem(n(N+1+select)*G,g_n(N+1+select),'r','linewidth',2);hold off
title('Impulsraum/Amplituden der deBroglie Wellen')
xlabel('k')
axis([-80,80, -0.05, y_max])

pause

figure(3)

plot(x,real(Psi),'r')
title('Ortsraum')
xlabel('Position x')
ylabel('Re [\Psi (x)]')

%  axis([-10 10 -1e-12,1e-12])   - in this zoom one can see oscillations

%% ********************************************************************

% Darstellung der einzelnen Summanden

x = -10:0.01:10;
Psi = 0*x;
g_n(N+1)=g_n(N+1)/2;

for cntr = 0:50, 
    Psi = Psi + 2*g_n(N+1+cntr)*cos(n(N+1+cntr)*G*x); 
end;

g_n(N+1)=g_n(N+1)*2;
Psi_b = 0*x;



for cntr = 0:50, 

    figure(3)
    %
    
    stem(n,g_n,'k'); hold on; 
    stem(n(N+1-cntr:N+1+cntr),g_n(N+1-cntr:N+1+cntr),'r'); 
    stem(n([N+1-cntr-1,N+1+cntr+1]),g_n([N+1-cntr-1,N+1+cntr+1]),'b');hold off
    xlabel('k')
    g_n(N+1)=g_n(N+1)/2;
    Psi_b = Psi_b + 2*g_n(N+1+cntr)*cos(n(N+1+cntr)*G*x);    
    g_n(N+1)=g_n(N+1)*2;
    
    figure(4)
    plot(x,real(Psi),'k','linewidth',2);hold on;
    plot(x,real(Psi_b),'r'); 
    plot(x,2*g_n(N+1+cntr+1)*cos(n(N+1+cntr+1)*G*x),'b');
    hold off
    
    pause;
end;

    


%%

% take one out deBroglie waves = \Psi \propto cos(Gx) 
G = 1;   % 5  or 0.2
Psi = 0*x;

select = -N:N;

%g_n(N+1+20)= 0 ;   take out 20 
%g_n(N+1-20)= 0 ;   take out 20

for cntr = select, 
    Psi = Psi + g_n(N+1+cntr)*exp(i*n(N+1+cntr)*G*x); 
 end;

figure(2)
stem(n*G,g_n,'b'); hold on; stem(n(N+1+select)*G,g_n(N+1+select),'r','linewidth',2);hold off
title('Impulsraum/Amplituden der deBroglie Wellen')
xlabel('k')
axis([-80,80, -0.05, y_max])

pause

figure(3)

plot(x,real(Psi),'r')
title('Ortsraum')
xlabel('Position x')
ylabel('Re [\Psi (x)]')
