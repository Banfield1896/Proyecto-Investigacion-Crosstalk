% Script de prueba
clc; clear; close all;
D = 1; dp = 0.2; do = 0.18; beta = 0.01; nSamplesIR = 4096; fs = 44100;
[cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(D, dp, do, beta, nSamplesIR, fs);

% Normalizar y visualizar para verificar los valores
cLL_norm = cLL / max(abs(cLL));
cLR_norm = cLR / max(abs(cLR));

figure;
plot(cLL_norm);
title('Respuesta al Impulso cLL Normalizada');

figure;
plot(cLR_norm);
title('Respuesta al Impulso cLR Normalizada');

% Verifica si hay valores NaN o Inf
if any(isnan(cLL)) || any(isinf(cLL))
    disp('La IR contiene valores no válidos (NaN o Inf).');
end