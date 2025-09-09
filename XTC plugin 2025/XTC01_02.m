classdef XTC01_02 < audioPlugin %& matlab.System % & matlab.system.mixin.Propagates
    properties
        D = 1.0               % Distancia plano altavoces-oídos (m)
        dp = 0.2              % Distancia entre altavoces (m)
        do = 0.18             % Distancia entre oídos (m)
        beta = 0.01           % Coeficiente de regularización
        nSamplesIR = 4096     % Cantidad de muestras de la IR
    end
   
    properties(Access = private)
        % ImpulseResponseDirect
        % Specify the direct impulse responses (hLL, hLR) from a stereo file.
        ImpulseResponse; % Que lo lea la concha de su madre. Expects 2-channel: [hL; hR]

        % PartitionSize Length of each partition of the impulse reponse
        PartitionSize = 4096; %2048; %1024;
        pFIR_hL_xL % Filter for hL * xL
        pFIR_hLR_xR % Filter for hLR * xR
        pFIR_hRL_xL % Filter for hRL * xL
        pFIR_hR_xR % Filter for hR * xR
    end    

    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}), ...
            audioPluginParameter('nSamplesIR', 'DisplayName', 'Muestras IR', 'Mapping', {'lin', 1024, 8192}), ...
            'InputChannels',2,... % Stereo input
            'OutputChannels',2,... % Stereo output
            'PluginName','CrosstalkConvolver'...
            );
    end

    

    methods(Access = protected)        
        function updateImpulseResponse(plugin)
            fs = getSampleRate(plugin);
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
            plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);

            plugin.ImpulseResponse = [cLL.'; cLR.']; % Transpuesta para [hL; hLR]
            plugin.setupFilters(); % Actualiza los filtros
        end

        function y = process(plugin,u)
            % u is the input audio, N-by-2 for stereo
            xL = u(:,1); % Left input channel
            xR = u(:,2); % Right input channel

            % Perform individual convolutions
            conv_hL_xL = step(plugin.pFIR_hL_xL, xL);
            conv_hLR_xR = step(plugin.pFIR_hLR_xR, xR);
            conv_hRL_xL = step(plugin.pFIR_hRL_xL, xL);
            conv_hR_xR = step(plugin.pFIR_hR_xR, xR);

            % Combine results as per the desired equations
            uL = conv_hL_xL + conv_hLR_xR; % uL = hL * xL + hLR * xR
            uR = conv_hRL_xL + conv_hR_xR; % uR = hRL * xL + hR * xR

            % Combine the output channels
            y = [uL, uR];
        end

        function setupImpl(plugin, u)
            plugin.updateImpulseResponse();      % Genera la IR con los parámetros actuales
            plugin.setupFilters(u);              % Configura los filtros con esa IR
        end

        function setupFilters(plugin, u)
            % Validate impulse response dimensions
            if size(plugin.ImpulseResponse, 1) ~= 2
                error('The ImpulseResponseDirect must be a stereo (2-channel) audio file.');
            end

            % Initialize all four FIR filters
            plugin.pFIR_hL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(1,:), ... % hL
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hL_xL, u(:,1)); % Setup with left input

            plugin.pFIR_hLR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(2,:), ... % hLR
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hLR_xR, u(:,2)); % Setup with right input

            plugin.pFIR_hRL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(2,:), ... % hRL
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hRL_xL, u(:,1)); % Setup with left input

            plugin.pFIR_hR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(1,:), ... % hR
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hR_xR, u(:,2)); % Setup with right input
        end       

        function resetImpl(plugin)
            % Reset all four FIR filters
            reset(plugin.pFIR_hL_xL);
            reset(plugin.pFIR_hLR_xR);
            reset(plugin.pFIR_hRL_xL);
            reset(plugin.pFIR_hR_xR);
        end       

        % Propagators (remain the same as they handle size and type based on input)
        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
        end

        function varargout = getOutputSizeImpl(obj)
            varargout{1} = propagatedInputSize(obj, 1);
        end

        function varargout = getOutputDataTypeImpl(obj)
            varargout{1} = propagatedInputDataType(obj, 1);
        end

        function varargout = isOutputFixedSizeImpl(obj)
            varargout{1} = propagatedInputFixedSize(obj,1);
        end
    end

    methods
        function set.D(plugin, val)
            plugin.D = val;
            plugin.updateImpulseResponse();
        end
        function set.dp(plugin, val)
            plugin.dp = val;
            plugin.updateImpulseResponse();
        end
        function set.do(plugin, val)
            plugin.do = val;
            plugin.updateImpulseResponse();
        end
        function set.beta(plugin, val)
            plugin.beta = val;
            plugin.updateImpulseResponse();
        end
        function set.nSamplesIR(plugin, val)
            allowed = [1024, 2048, 4096, 8192];
            if ~ismember(val, allowed)
                error('nSamplesIR debe ser uno de los siguientes valores: 1024, 2048, 4096, 8192');
            end
            plugin.nSamplesIR = val;
            plugin.updateImpulseResponse();
            %plugin.setupFilters(zeros(val, 2)); % o el tamaño que uses

        end
    end
end