classdef XTC02 < audioPlugin
    properties
        D = 1.0               % Distancia plano altavoces-oídos (m)
        dp = 0.2              % Distancia entre altavoces (m)
        do = 0.18             % Distancia entre oídos (m)
        beta = 0.01           % Coeficiente de regularización
        nSamplesIR = 4096     % Cantidad de muestras de la IR
    end
    
    properties(Access = private)
        % Respuesta al impulso inicial (stereo)
        ImpulseResponse = audioread('respuestaImpulsoXTC.wav').'; 
        PartitionSize = 4096;
    end

    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}), ...
            audioPluginParameter('nSamplesIR', 'DisplayName', 'Muestras IR', 'Mapping', {'lin', 1024, 8192}), ...
            'InputChannels',2,...
            'OutputChannels',2,...
            'PluginName','CrosstalkConvolver'...
            );
    end

    properties(Access = private)
        pFIR_hL_xL
        pFIR_hLR_xR
        pFIR_hRL_xL
        pFIR_hR_xR
    end    

    methods (Access = private)
        function updateImpulseResponse(plugin)
            fs = getSampleRate(plugin);
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);

            plugin.ImpulseResponse = [cLL.'; cLR.']; 
            plugin.setupFilters(); 
        end

        function setupFilters(plugin)
            if size(plugin.ImpulseResponse, 1) ~= 2
                error('ImpulseResponse debe tener 2 canales (stereo).');
            end

            plugin.pFIR_hL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(1,:), ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);

            plugin.pFIR_hLR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(2,:), ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);

            plugin.pFIR_hRL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(2,:), ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);

            plugin.pFIR_hR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(1,:), ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);
        end
    end

    methods
        function y = process(plugin, u)
            % Entrada stereo
            xL = u(:,1);
            xR = u(:,2);

            % Convoluciones
            conv_hL_xL  = plugin.pFIR_hL_xL(xL);
            conv_hLR_xR = plugin.pFIR_hLR_xR(xR);
            conv_hRL_xL = plugin.pFIR_hRL_xL(xL);
            conv_hR_xR  = plugin.pFIR_hR_xR(xR);

            % Mezcla
            uL = conv_hL_xL + conv_hLR_xR;
            uR = conv_hRL_xL + conv_hR_xR;

            % Salida stereo
            y = [uL, uR];
        end

        % Setters que actualizan IR
        function set.D(plugin, val), plugin.D = val; plugin.updateImpulseResponse(); end
        function set.dp(plugin, val), plugin.dp = val; plugin.updateImpulseResponse(); end
        function set.do(plugin, val), plugin.do = val; plugin.updateImpulseResponse(); end
        function set.beta(plugin, val), plugin.beta = val; plugin.updateImpulseResponse(); end
        function set.nSamplesIR(plugin, val)
            allowed = [1024, 2048, 4096, 8192];
            if ~ismember(val, allowed)
                error('nSamplesIR debe ser 1024, 2048, 4096 o 8192');
            end
            plugin.nSamplesIR = val;
            plugin.updateImpulseResponse();
        end
    end
end
