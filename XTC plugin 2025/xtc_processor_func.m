function out = xtc_processor_func(in, params)
% xtc_processor_func - DSP core for the Crosstalk plugin.
% This version uses a functional approach with persistent variables,
% making it compatible with older versions of MATLAB Coder like R2017b.

% %% CAMBIO CLAVE: Declarar los filtros como variables persistentes.
% Estas variables se crear�n una sola vez y mantendr�n su estado
% entre las llamadas a esta funci�n.
nSamplesIR=8192;
persistent pFilter_LL pFilter_RL pFilter_LR pFilter_RR isInitialized

% On the very first run, or if the sample rate changes, initialize.
if isempty(isInitialized)
    % Crear los objetos de filtro por primera vez
    pFilter_LL = dsp.FrequencyDomainFIRFilter;
    pFilter_RL = dsp.FrequencyDomainFIRFilter;
    pFilter_LR = dsp.FrequencyDomainFIRFilter;
    pFilter_RR = dsp.FrequencyDomainFIRFilter;

    % Calcular la IR inicial con los par�metros por defecto
    [cLL, cLR] = transaural_ir3(...
        params.D, params.dp, params.do, params.beta, nSamplesIR, params.SampleRate);
    
    % Asignar los numeradores a los filtros
    pFilter_LL.Numerator = cLL.';
    pFilter_RL.Numerator = cLR.';
    pFilter_LR.Numerator = cLR.';
    pFilter_RR.Numerator = cLL.';
    
    isInitialized = true;
end

% --- Actualizaci�n de Par�metros (si es necesario) ---
% En un plugin real, esto se llamar�a solo cuando un par�metro cambia.
% Aqu�, para la generaci�n de c�digo, asumimos que 'params' puede cambiar
% en cada llamada, as� que recalculamos.
[cLL, cLR] = transaural_ir3(...
    params.D, params.dp, params.do, params.beta, nSamplesIR, params.SampleRate);

pFilter_LL.Numerator = cLL.';
pFilter_RL.Numerator = cLR.';
pFilter_LR.Numerator = cLR.';
pFilter_RR.Numerator = cLL.';

% --- Procesamiento de Audio ---
left_in = in(:,1);
right_in = in(:,2);

% Usar 'step' en los objetos de filtro persistentes
y_LL = step(pFilter_LL, left_in);
y_RL = step(pFilter_RL, right_in);
y_LR = step(pFilter_LR, left_in);
y_RR = step(pFilter_RR, right_in);

% Combinar las salidas
outL = y_LL + y_RL;
outR = y_LR + y_RR;

out = [outL, outR];
end