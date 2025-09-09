% Simulaci�n de entrada est�reo
fs = 48000;
t = 0:1/fs:1;
in = [sin(2*pi*440*t)', sin(2*pi*880*t)'];

% Inicializaci�n de filtros
plugin.pFIRL = dsp.FrequencyDomainFIRFilter('Numerator', irL, 'PartitionLength', 8192);
plugin.pFIRR = dsp.FrequencyDomainFIRFilter('Numerator', irR, 'PartitionLength', 8192);

% Procesamiento
outL = plugin.pFIRL(in(:,1));
outR = plugin.pFIRR(in(:,2));

% Visualizaci�n
figure;
subplot(2,1,1); plot(outL); title('Canal Izquierdo');
subplot(2,1,2); plot(outR); title('Canal Derecho');