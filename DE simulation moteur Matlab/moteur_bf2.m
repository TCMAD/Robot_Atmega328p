
R = 5;
L = 1e-3;
J = 1.37e-4;
f = 6.79e-5;
k = 0.209;
Kp = 1;
E = 50;
Cr=0.02068;
Tsim=4;
Kc = 5.5;
Ki = 0;
Kd = 0;

% réponse sans correcteur %
sim('moteur',Tsim)
figure(10)
subplot(3,1,1)
plot(omega.time,omega.data)
title('Simulation reponse moteur sans correcteur')

subplot(3,1,2)
plot(omega.time,omega.data)
axis([0 0.01 0 50])
title('Temps de réponse')

subplot(3,1,3)
plot(omega.time,omega.data)
axis([2 3 47 50])
title('Influence de Cr')


% Influence de Kp %
Kp = 1;
sim('moteur',Tsim)
figure(11)
subplot(3,1,1)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Kp = 1')
axis([0 0.05 0 60])

Kp = 2;
sim('moteur',Tsim)
subplot(3,1,2)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Kp = 2')
axis([0 0.05 0 60])

Kp = 4;
sim('moteur',Tsim)
subplot(3,1,3)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Kp = 4')
axis([0 0.05 0 60])

% Zoom
Kp = 1;
sim('moteur',Tsim)
figure(12)
subplot(3,1,1)
plot(omega.time,omega.data)
title('Zoom : Kp = 1')
axis([0 0.02 40 60])

Kp = 2;
sim('moteur',Tsim)
subplot(3,1,2)
plot(omega.time,omega.data)
title('Zoom : Kp = 2')
axis([0 0.02 40 60])

Kp = 4;
sim('moteur',Tsim)
subplot(3,1,3)
plot(omega.time,omega.data)
title('Zoom : Kp = 4')
axis([0 0.02 40 60])


% Influence de Ki %
Kp = 4;
Ki = 1;
sim('moteur',Tsim)
figure(13)
subplot(3,1,1)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Ki = 1')
axis([0 0.02 40 60])

Ki = 2;
sim('moteur',Tsim)
subplot(3,1,2)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Ki = 2')
axis([0 0.02 40 60])

Ki = 10;
sim('moteur',Tsim)
subplot(3,1,3)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Ki = 10')
axis([0 0.02 40 60])

% Observation de l'erreur statique %
Ki = 1;
sim('moteur',Tsim)
figure(15)
subplot(2,1,1)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Ki = 1')
axis([0 4 45 55])

Ki = 2;
sim('moteur',Tsim)
subplot(2,1,2)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de réponse avec Ki = 2')
axis([0 4 45 55])


% influence de Kd %
Kp = 4;
Ki = 2;
Kd = 1;
sim('moteur',Tsim)
figure(14)
plot(omega.time,omega.data)
title('Simulation reponse indicielle moteur : temps de montee avec Kd = 1')
axis([0 0.02 40 60])