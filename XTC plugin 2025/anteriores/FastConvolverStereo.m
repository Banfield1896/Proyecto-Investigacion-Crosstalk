classdef FastConvolverStereo < audioPlugin & matlab.System & ...
        matlab.system.mixin.Propagates
    properties(Nontunable)
        % ImpulseResponse
        % Specify the impulse response for convolution, as a matrix.
        % 'response.wav' file should be stereo.
        ImpulseResponse = audioread('response_st.wav').'; % Ensure it's 2-channel: [L; R]
        % PartitionSize Length of each partition of the impulse reponse
        % Specify the length of each partition of the impulse reponse, as
        % a finite positive integer scalar. The default value of this
        % property is 1024.
        PartitionSize = 1024;
    end

    properties (Constant)
        % audioPluginInterface manages the number of input/output channels
        % and uses audioPluginParameter to generate plugin UI parameters.
        PluginInterface = audioPluginInterface(...
            'InputChannels',2,... % Set to 2 for stereo input
            'OutputChannels',2,... % Set to 2 for stereo output
            'PluginName','StereoFastConvolver'...
            );
    end

    properties(Access = private, Nontunable)
        pFIR_L % FIR filter for the left channel
        pFIR_R % FIR filter for the right channel
    end

    methods(Access = protected)
        function y = stepImpl(plugin,u)
            % u is the input audio, which will be N-by-2 for stereo
            % Split input into left and right channels
            uL = u(:,1);
            uR = u(:,2);

            % Convolve each channel independently
            yL = step(plugin.pFIR_L,uL);
            yR = step(plugin.pFIR_R,uR);

            % Combine the output channels
            y = [yL, yR];
        end

        function setupImpl(plugin, u)
            % Ensure the ImpulseResponse is stereo (2 rows)
            if size(plugin.ImpulseResponse, 1) ~= 2
                error('The ImpulseResponse must be a stereo (2-channel) audio file.');
            end

            % Create separate FIR filters for left and right channels
            plugin.pFIR_L = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(1,:), ... % Left channel impulse response
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);

            plugin.pFIR_R = dsp.FrequencyDomainFIRFilter(...
                'Numerator', plugin.ImpulseResponse(2,:), ... % Right channel impulse response
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.PartitionSize);

            % Setup the filters with a single channel input
            setup(plugin.pFIR_L, u(:,1));
            setup(plugin.pFIR_R, u(:,2));
        end

        function resetImpl(plugin)
            % Initialize / reset discrete-state properties
            reset(plugin.pFIR_L);
            reset(plugin.pFIR_R);
        end

        %------------------------------------------------------------------
        % Propagators
        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
        end

        function varargout = getOutputSizeImpl(obj)
            % Output size will be the same as input size
            varargout{1} = propagatedInputSize(obj, 1);
        end

        function varargout = getOutputDataTypeImpl(obj)
            % Output data type will be the same as input data type
            varargout{1} = propagatedInputDataType(obj, 1);
        end

        function varargout = isOutputFixedSizeImpl(obj)
            % Output fixed size will be the same as input fixed size
            varargout{1} = propagatedInputFixedSize(obj,1);
        end
    end
end