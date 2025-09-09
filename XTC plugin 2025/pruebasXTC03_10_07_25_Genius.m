% Calcula la matriz C de cancelaci�n de crosstalk
% Caso sim�trico sin reflexiones en la cabeza
% D es la distancia del plano de altavoces al plano o�dos
% dp es la distancia entre altavoces
% do es la distancia entre o�dos
% beta es el coeficiente de regulaci�n
% nmuestras es la cant de muestras de las transferencias (con resol. de 1
% Hz coincidir�a con fs)
% fs es la frecuencia de muestreo
% C es la matriz de cancelaci�n de crosstalk
% H es la matriz desde altavoces hasta o�dos
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

% Nueva versi�n con un solo archivo wav de configuraci�n LL LR
audiowrite('respuestaImpulsoXTC.wav',[cLL, cRL],fs);

