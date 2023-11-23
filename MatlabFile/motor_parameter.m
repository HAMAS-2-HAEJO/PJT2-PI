%DC Motor Param
J = 2.09*10^(-5);
Kb = 0.042;
Kt = 0.042;
R = 8.4; 
L = 1.16;
B = 0.0003;

Kp = 0.5;
Ki =  0.8;
Kd = 0;

Wconst = 60;

%Distance Param
Kdp = 0.6;
Kdi = 0.7;
Kdd = 0;

Ldes = 20;


%Scenario#1 Param
Sconst1 = 50;



%poly
D1 = [J*L J*R+L*B R*B+Kt*Kb];
N1=[Kt];
H = (N1(1) - D1(3))/N1(1);

%Matrix
A=[0 1 0; 0 -B/J Kt/J; 0 -Kb/L -R/L];
Bm = [0 0 1/L]';
C = [1 0 0];
D = 0;

%Observer Gain
Lo = acker(A', C', [-50 -100 -150]);

LPF2=tf([100*100],[1 200 100*100]);
