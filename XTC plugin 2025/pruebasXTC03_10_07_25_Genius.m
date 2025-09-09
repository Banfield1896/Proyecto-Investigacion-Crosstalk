% Calcula la matriz C de cancelación de crosstalk
% Caso simétrico sin reflexiones en la cabeza
% D es la distancia del plano de altavoces al plano oídos
% dp es la distancia entre altavoces
% do es la distancia entre oídos
% beta es el coeficiente de regulación
% nmuestras es la cant de muestras de las transferencias (con resol. de 1
% Hz coincidiría con fs)
% fs es la frecuencia de muestreo
% C es la matriz de cancelación de crosstalk
% H es la matriz desde altavoces hasta oídos
fs=44100;
D=0.25; dp=0.08; do=0.19; beta=1*0.1; %nmuestras=fs; nmuestrasNyquist=fs/2;
%D=0.9; dp=0.5; do=0.19; beta=1*0.02; %nmuestras=fs; nmuestrasNyquist=fs/2;
nSamplesIR=fs/10;
%[C, H, condH, condC] = matrizXTC(D,dp,do,beta,nmuestrasNyquist,fs);
%[cLL,cRL, cLR, cRR, t, dt,C,H] = transaural_ir(D,dp,do,beta,nSamplesIR,fs);
[cLL,cRL] = transaural_ir(D,dp,do,beta,nSamplesIR,fs);
cmaxLL=max(cLL);cmaxRL=max(cRL);
cmax=max(cmaxLL,cmaxRL);
cLL=0.5/cmax*cLL; cRL=0.5/cmax*cRL;

% Nueva versión con un solo archivo wav de configuración LL LR
audiowrite('respuestaImpulsoXTC.wav',[cLL, cRL],fs);

