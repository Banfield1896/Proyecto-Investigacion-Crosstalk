classdef CrosstalkConvolver < audioPlugin & matlab.System & ...
        matlab.system.mixin.Propagates
    properties(Nontunable)
        % ImpulseResponseDirect
        % Specify the direct impulse responses (hL, hR) from a stereo file.
        ImpulseResponseDirect = audioread('cLL_RR.wav').'; % Expects 2-channel: [hL; hR]

        % ImpulseResponseCrossLR
        % Specify the cross impulse response for Left output from Right input (hLR).
        % Expected to be a mono WAV file.
        ImpulseResponseCrossLR = audioread('cLR.wav').'; % Expects 1-channel: hLR

        % ImpulseResponseCrossRL
        % Specify the cross impulse response for Right output from Left input (hRL).
        % Expected to be a mono WAV file.
        ImpulseResponseCrossRL = audioread('cRL.wav').'; % Expects 1-channel: hRL

        % PartitionSize Length of each partition of the impulse reponse
        PartitionSize = 4096; %2048; %1024;
    end

    properties (Constant)
        PluginInterface = audioPluginInterface(...
            'InputChannels',2,... % Stereo input
            'OutputChannels',2,... % Stereo output
            'PluginName','CrosstalkConvolver'...
            );
    end

    properties(Access = private, Nontunable)
        pFIR_hL_xL % Filter for hL * xL
        pFIR_hLR_xR % Filter for hLR * xR
        pFIR_hRL_xL % Filter for hRL * xL
        pFIR_hR_xR % Filter for hR * xR
    end

    methods(Access = protected)
        function y = stepImpl(plugin,u)
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
            % Validate impulse response dimensions
            if size(plugin.ImpulseResponseDirect, 1) ~= 2
                error('The ImpulseResponseDirect must be a stereo (2-channel) audio file.');
            end
            if size(plugin.ImpulseResponseCrossLR, 1) ~= 1
                error('The ImpulseResponseCrossLR must be a mono (1-channel) audio file.');
            end
            if size(plugin.ImpulseResponseCrossRL, 1) ~= 1
                error('The ImpulseResponseCrossRL must be a mono (1-channel) audio file.');
            end

            % Initialize all four FIR filters
            plugin.pFIR_hL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponseDirect(1,:), ... % hL
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hL_xL, u(:,1)); % Setup with left input

            plugin.pFIR_hLR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponseCrossLR(1,:), ... % hLR
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hLR_xR, u(:,2)); % Setup with right input

            plugin.pFIR_hRL_xL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponseCrossRL(1,:), ... % hRL
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR_hRL_xL, u(:,1)); % Setup with left input

            plugin.pFIR_hR_xR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponseDirect(2,:), ... % hR
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
end