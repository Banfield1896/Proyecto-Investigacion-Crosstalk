function [cLL, cLR] = transaural_ir(D, dp, do, beta, nSamplesIR, fs)
% Calcula las respuestas al impulso de cancelaci�n de crosstalk
% La c min�scula se utiliza aqu� para funciones del tiempo
% La C may�scula para funciones de la frecuencia
% D es la distancia del plano de altavoces al plano o�dos
% dp es la distancia entre altavoces
% do es la distancia entre o�dos
% beta es el coeficiente de regulaci�n
% nSamplesIR es la cant de muestras de las rtas al impulso
% fs es la frecuencia de muestreo
% C es la matriz de cancelaci�n de crosstalk
% --- Caso sim�trico sin reflexiones en la cabeza
% --- Pre-asignaci�n de memoria ---
% Es lo mas eficiente y resulta necesario para pasar el codigo a C++ en el
% futuro
C = complex(zeros(2, 2, nSamplesIR/2));
% H no es necesario si no se devuelve H2.
% C2 y H2 tampoco son necesarios si no se devuelven.

c = 345;

f = (0:nSamplesIR/2-1) / nSamplesIR * fs;

dLL = sqrt(D^2 + (dp/2 - do/2)^2);
dLR = sqrt(D^2 + (dp/2 + do/2)^2);
tLL = dLL/c;
tLR = dLR/c;

% C�lculo de la matriz de transferencia en frecuencia
for naux = 1:nSamplesIR/2
    w = 2 * pi * f(naux);
    Haux0 = [exp(-1i*w*tLL)/dLL, exp(-1i*w*tLR)/dLR; ...
             exp(-1i*w*tLR)/dLR, exp(-1i*w*tLL)/dLL];
    C(:,:,naux) = inv((Haux0' * Haux0 + beta * eye(2))) * Haux0';
end

% Reconstrucci�n del espectro completo
CLL_spec = [squeeze(C(1,1,:)); 0; conj(squeeze(C(1,1,end:-1:2)))];
CLR_spec = [squeeze(C(2,1,:)); 0; conj(squeeze(C(2,1,end:-1:2)))];

% Obtener la respuesta al impulso (real)
cLL = real(ifft(CLL_spec));
cLR = real(ifft(CLR_spec));

% Aplicar un peque�o retardo para hacer la respuesta causal
tdelay = 0.01; % 10 ms delay
ntdelay = round(tdelay * fs);
cLL = circshift(cLL, ntdelay);
cLR = circshift(cLR, ntdelay);

end