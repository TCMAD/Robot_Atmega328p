clear all
close all
clc

% Parametre Monmasson %
R = 7;
L = 3.5e-3;
J = 5e-3;
f = 10e-3;
k = 0.5;
Kp = 1;
E=50;
Cr=0.1;
Tsim=4;
Kc = 5.5;
Ki = 0;

% temps de montee sans correcteur %
sim('moteur',Tsim)
figure(10)
plot(omega.time,omega.data)


% Parametre Verifie %
R = 5;
L = 3.5e-3;
J = 1.37e-3;
f = 6.79e-5;
k = 0.209;
Kp = 7;
E=50;
Cr=0.02068;
Tsim=4;
Kc = 5.5;
Ki = 0;

% temps de montee sans correcteur %
sim('moteur',Tsim)
figure(16)
plot(omega.time,omega.data)


R = 5;
L = 1e-3;
J = 1.37e-4;
f = 6.79e-5;
k = 0.209;
Kp = 1;
E=50;
Cr=0.02068;
Tsim=1;
Kc = 5.5;
Ki = 0;

% % temps de montee sans correcteur %
% sim('moteur',Tsim)
% figure(15)
% plot(omega.time,omega.data)
% 
% 
% % Influence de Kp %
% Kp = 8;
% sim('moteur',Tsim)
% figure(11)
% plot(omega.time,omega.data)
% 
% % Influence de Ki %
% Ki = 5;
% sim('moteur',Tsim)
% figure(12)
% plot(omega.time,omega.data)