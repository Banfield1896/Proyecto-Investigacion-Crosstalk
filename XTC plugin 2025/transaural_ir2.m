function [cLL,cRL, cLR, cRR, t, dt, C2, H2] = transaural_ir2(D,dp,do,beta,nSamplesIR,fs)
% [cLL,cRL, cLR, cRR, t, dt] = transaural_ir(D,dp,do,beta,nSamplesIR,fs);
% Calcula las respuestas al impulso de cancelación de crosstalk
% ... (descripción sin cambios)

c=345; % Velocidad del sonido en m/s
if mod(nSamplesIR,2)==1 
    disp('Warning! nSamplesIR is expected to be an even number');
    disp('It was automatically fix adding one to the value proposed.')
    nSamplesIR=nSamplesIR+1;
end
f=(0:nSamplesIR-1)/nSamplesIR*fs;
dLL = sqrt(D^2+(dp/2-do/2)^2); % Distancia ipsilateral
dLR = sqrt(D^2+(dp/2+do/2)^2); % Distancia contralateral
tLL=dLL/c; tLR=dLR/c; 

% Cálculo de las matrices de transferencia
H=complex(zeros(2,2,nSamplesIR/2+1));
C=complex(zeros(2,2,nSamplesIR/2+1));

% El bucle debe ir hasta nSamplesIR/2 + 1 para incluir Nyquist
for naux = 1:(nSamplesIR/2+1)
    w=2*pi*f(naux);
    Haux0=[exp(-1i*w*tLL)/dLL,        exp(-1i*w*tLR)/dLR; ...
           exp(-1i*w*tLR)/dLR,        exp(-1i*w*tLL)/dLL];
    
    % Inversión regularizada para obtener el filtro de cancelación
    C(:,:,naux)=inv(Haux0'*Haux0 + beta*eye(2)) * Haux0';
    H(:,:,naux)=Haux0;
end

% Reconstrucción del espectro completo (Hermitian symmetric)
CLL_spec = [squeeze(C(1,1,:)); conj(squeeze(C(1,1,end-1:-1:2)))];
CLR_spec = [squeeze(C(2,1,:)); conj(squeeze(C(2,1,end-1:-1:2)))];
CRR_spec = CLL_spec; % Por simetría
CRL_spec = CLR_spec;

HLL_spec = [squeeze(H(1,1,:)); conj(squeeze(H(1,1,end-1:-1:2)))];
HLR_spec = [squeeze(H(2,1,:)); conj(squeeze(H(2,1,end-1:-1:2)))];
HRR_spec = HLL_spec;
HRL_spec = HLR_spec;

C2(1,1,:) = CLL_spec; C2(1,2,:) = CLR_spec; C2(2,1,:) = CRL_spec; C2(2,2,:) = CRR_spec;
H2(1,1,:) = HLL_spec; H2(1,2,:) = HLR_spec; H2(2,1,:) = HRL_spec; H2(2,2,:) = HRR_spec;

% %% CAMBIO: Usar real() para descartar residuos imaginarios por errores de precisión
% La transformada inversa de un espectro Hermítico es siempre real.
cLL = real(ifft(CLL_spec));
cLR = real(ifft(CLR_spec));

% Centrar el pico de la IR para evitar 'wrap-around'
tdelay = 0.01; % 10 ms
ntdelay = round(tdelay * fs);
cLL = circshift(cLL, ntdelay);
cLR = circshift(cLR, ntdelay);

% Por simetría
cRR = cLL; 
cRL = cLR;

dt = 1/fs;
t = (0:length(cLL)-1)*dt;

end
