

x =(-20:0.01:20)'
;   % space coordinate in units of harmonic oscillator length

H = zeros(length(x),100);

H(:,1) = 1;
H(:,2) = 2*x;

for n = 3 :100,
    H(:,n) = 2*x.*H(:,n-1) - 2*(n-2)*H(:,n-2);
end;


% harmonic oscillator states:

phi = zeros(length(x),100);

for n = 1:100,
    phi(:,n)=1/pi^0.25/sqrt(2^(n-1)*factorial(n-1))*H(:,n).*exp(-0.5*x.^2);
end;


figure(1);

%% klassischer Umkehrpunkt für Energie des n-ten Quantenzustand
n= 0;

x_klassisch = sqrt(2*(n+0.5));

figure(2)
plot([x_klassisch x_klassisch],[0 1],'k',[-x_klassisch -x_klassisch],[0 1],'k')
hold on
plot(x,abs(phi(:,n+1)).^2)
text(x_klassisch+0.1,max(abs(phi(:,n+1)).^2)/2,'klassischer Umkehrpunkt')
hold off
axis([min(x) max(x) 0 max(abs(phi(:,n+1)).^2)])
    


%% oszillierendes Wellenpaket


Psi_in = circshift(phi(:,1),1200);     % shift of 100 corresponds to 1 oscillator length

c= zeros(1,100);
for n=1:100,
    c(n) = sum(phi(:,n).*Psi_in)*(x(2)-x(1));
end;

Psi_sum = Psi_in*0;

for n=1:100,
    Psi_sum = Psi_sum+c(n)*phi(:,n);
end;



figure(3)
plot(x,Psi_in,x,phi(:,1),x,Psi_sum,'g')

% calculate Matrixelements:

c= zeros(1,100);
for n=1:100,
    c(n) = sum(phi(:,n).*Psi_in)*(x(2)-x(1));
end;


%% time dynamics as interference of energy eigenstates


figure(5)
for t = 0:0.01:1,

    Psi_t = Psi_in*0;
    
    for n=1:100,
        Psi_t = Psi_t + exp(i*(n-0.5)*2*pi*t)*c(n)*phi(:,n);
    end;
    
    subplot(2,1,1)
    plot(x,abs(Psi_t).^2);
    xlabel('position [a_{ho}]')
    ylabel('probability')
    
    subplot(2,1,2)
    plot(x,real(Psi_t));
    xlabel('position [a_{ho}]')
    ylabel('real part of \Psi (t)')
    axis([-20 20 -1 1])
    
    drawnow
    pause(0.1)
end;




    
        
        
        
    
    
    
    
    
    


    
    
    
    
