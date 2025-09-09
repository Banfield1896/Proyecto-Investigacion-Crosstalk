classdef XTC_Processor < matlab.System
    % XTC_Processor - DSP core for the Crosstalk plugin.
    % This version is robust for C++ code generation by initializing
    % all object properties in the constructor.

    % Public properties that will be our parameters in JUCE
    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
    end

    % Private properties for internal state
    properties (Access = private)
        % Filter objects. They are now initialized in the constructor.
        pFilter_LL; pFilter_RL; pFilter_LR; pFilter_RR;
        
        % IR settings
        pSampleRate = 44100;
        pSamplesIR = 8192;
    end

    methods
        % Constructor
        function obj = XTC_Processor()
            % %% CAMBIO CLAVE: Inicializar los objetos aquí.
            % Ahora, MATLAB Coder sabe desde el principio que estas
            % propiedades SIEMPRE serán de la clase 'dsp.FrequencyDomainFIRFilter'.
            obj.pFilter_LL = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_RL = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_LR = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_RR = dsp.FrequencyDomainFIRFilter;
        end

        % Method to update parameters from the GUI
        function updateParameters(obj, D, dp, do, beta)
            obj.D = D;
            obj.dp = dp;
            obj.do = do;
            obj.beta = beta;

            % Recalculate IRs and update filter numerators
            [cLL, ~, cLR, ~] = transaural_ir(...
                obj.D, obj.dp, obj.do, obj.beta, obj.pSamplesIR, obj.pSampleRate);
            
            % Update the numerators of the existing filter objects
            obj.pFilter_LL.Numerator = cLL.';
            obj.pFilter_RL.Numerator = cLR.';
            obj.pFilter_LR.Numerator = cLR.';
            obj.pFilter_RR.Numerator = cLL.';
        end
    end

    methods (Access = protected)
        % setupImpl is called once at the beginning
        function setupImpl(obj, ~) % La entrada 'frame' ya no es necesaria aquí
            % %% CAMBIO CLAVE: Ya no se CREAN los objetos, solo se CONFIGURAN.
            [cLL, ~, cLR, ~] = transaural_ir(...
                obj.D, obj.dp, obj.do, obj.beta, obj.pSamplesIR, obj.pSampleRate);

            % Asignar los numeradores a los filtros que ya existen
            obj.pFilter_LL.Numerator = cLL.';
            obj.pFilter_RL.Numerator = cLR.';
            obj.pFilter_LR.Numerator = cLR.';
            obj.pFilter_RR.Numerator = cLL.';
            
            % Es importante resetear los filtros durante la configuración inicial
            resetImpl(obj);
        end

        % stepImpl is the main processing loop (equivalent to 'process')
        function out = stepImpl(obj, in)
            left_in = in(:,1);
            right_in = in(:,2);
            
            % Process audio through the four filters
            y_LL = step(obj.pFilter_LL, left_in);
            y_RL = step(obj.pFilter_RL, right_in);
            y_LR = step(obj.pFilter_LR, left_in);
            y_RR = step(obj.pFilter_RR, right_in);
            
            % Combine the outputs
            outL = y_LL + y_RL;
            outR = y_LR + y_RR;
            
            out = [outL, outR];
        end

        % resetImpl is called to reset the internal state
        function resetImpl(obj)
            reset(obj.pFilter_LL);
            reset(obj.pFilter_RL);
            reset(obj.pFilter_LR);
            reset(obj.pFilter_RR);
        end
    end
end