classdef FastConvolver < audioPlugin & matlab.System & ...
        matlab.system.mixin.Propagates
%FastConvolver Convolve input with large impulse responses and low latency.
%Time-domain convolution of an input frame with a long impulse response
%adds latency equal to the length of the impulse response. The algorithm in
%this plugin uses frequency-domain partitioned convolution to reduce the
%latency to the partition size. The efficiency of this algorithm enables
%real-time convolution with long impulse responses.
%
%   FC = audiopluginexample.FastConvolver() returns an object FC with
%   properties set to their default values.
%
%   process method syntax:
%
%   Y = process(FC, X) convolves the audio input X based on the properties
%   specified in the object FC and returns the output Y. Each column of X
%   is treated as an individual input channel.
%
%   FastConvolver methods:
%   
%   process   - See above description for use of this method
%   reset     - Reset the internal states to initial conditions
%
%   FastConvolver properties:
%
%   ImpulseResponse  - Impulse reponse convolved with input
%   PartitionSize    - Length of each partition of the impulse response
%
%   Reference: 
%   
%   Armelloni, Enrico, Christian Giottoli, and Angelo Farina.
%   "Implementation of real-time partitioned convolution on a DSP board."
%   In Applications of Signal Processing to Audio and Acoustics, 2003 IEEE
%   Workshop on., pp. 71-74. IEEE, 2003.
%
%   % Example 1: Construct and use a fast convolver with the impulse
%   % response of a large church.
%   reader = dsp.AudioFileReader('FunkyDrums-44p1-stereo-25secs.mp3', ...
%                 'SamplesPerFrame', 1024);
%
%   player = audioDeviceWriter('SampleRate', reader.SampleRate);
%
%   convolver = audiopluginexample.FastConvolver;
%
%   while ~isDone(reader)
%       x = reader();
%       y = convolver(x(:,1));
%       player(y);
%   end
%   release(reader)
%   release(player)
%
%   % Example 2: Validate and generate a VST plugin
%   validateAudioPlugin audiopluginexample.FastConvolver
%   generateAudioPlugin audiopluginexample.FastConvolver
%
%   % In order to generate the plugin for a different impulse response or a
%   % different partition size, edit the assignment to the ImpulseResponse
%   % or PartitionSize property in the class definition. Open the class 
%   % file by typing in the MATLAB Command Window: 
%   % edit audiopluginexample.FastConvolver
%
%   % Example 3: Launch a test bench for the FastConvolver object
%   convolver = audiopluginexample.FastConvolver;
%   audioTestBench(convolver);
%
%   % If you hear glitches in the audio played from audioTestBench, change
%   % 'Run As' mode to 'VST plugin'.
%
%   See also: dsp.FrequencyDomainFIRFilter, conv, fftfilt, dsp.Convolver 

%   Copyright 2016-2017 The MathWorks, Inc.
    
%#codegen

    properties(Nontunable)
        % ImpulseResponse Impulse response
        %   Specify the impulse response for convolution, as a vector. The
        %   default value of this property is a 5 second impulse response
        %   of a church loaded from
        %   ChurchImpulseResponse-16-44p1-mono-5secs.wav file.
        %ImpulseResponse = audioread('ChurchImpulseResponse-16-44p1-mono-5secs.wav').';
        ImpulseResponse = audioread('respuestaImpulso-44p1k-mono-5secs.wav').';
        % PartitionSize Length of each partition of the impulse reponse
        %   Specify the length of each partition of the impulse reponse, as
        %   a finite positive integer scalar. The default value of this
        %   property is 1024.
        PartitionSize = 1024;
    end
    
    properties (Constant)
        % audioPluginInterface manages the number of input/output channels
        % and uses audioPluginParameter to generate plugin UI parameters.
        PluginInterface = audioPluginInterface(...
            'InputChannels',1,...
            'OutputChannels',1,...
            'PluginName','FastConvolver'...
            );
    end

    properties(Access = private, Nontunable)
        pFIR
    end

    methods(Access = protected)
        function y = stepImpl(plugin,u)
            y = step(plugin.pFIR,u);
        end

        function setupImpl(plugin, u)
            plugin.pFIR = dsp.FrequencyDomainFIRFilter('Numerator', plugin.ImpulseResponse, ...
                'PartitionForReducedLatency', true, 'PartitionLength', plugin.PartitionSize);
            setup(plugin.pFIR, u);
        end

        function resetImpl(plugin)
            % Initialize / reset discrete-state properties
            reset(plugin.pFIR);
        end
        
        %------------------------------------------------------------------
        % Propagators
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